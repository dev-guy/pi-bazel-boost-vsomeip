#include <condition_variable>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <thread>

#include "vsomeip/vsomeip.hpp"
#include "gtest/gtest.h"

#define SAMPLE_SERVICE_ID 0x1234
#define SAMPLE_INSTANCE_ID 0x5678
#define SAMPLE_METHOD_ID 0x0421

namespace pecomp
{
namespace
{
  using namespace std;
  shared_ptr<vsomeip::application> app;
  mutex mutex_;
  condition_variable condition; // Fired when the client starts
  bool message_received = false;
  thread sender;

  void send_message()
  {
    using namespace std;

    shared_ptr<vsomeip::message> request;
    request = vsomeip::runtime::get()->create_request();
    request->set_service(SAMPLE_SERVICE_ID);
    request->set_instance(SAMPLE_INSTANCE_ID);
    request->set_method(SAMPLE_METHOD_ID);

    shared_ptr<vsomeip::payload> its_payload = vsomeip::runtime::get()->create_payload();
    vector<vsomeip::byte_t> its_payload_data;
    for(vsomeip::byte_t i = 0; i < 10; i++)
    {
      its_payload_data.push(i % 256);
    }
    its_payload->set_data(its_payload_data);
    request->set_payload(its_payload);

    unique_lock<mutex> its_lock(mutex_);
    condition.wait(its_lock); // Give up the lock, wait for client start, get it back

    app->send(request, true);
  }

  void stop()
  {
    using namespace std;
    sender.join();

    app->stop_offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
    app->unregister_state_handler();
    app->unregister_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID);
    app->stop();
  }

  void on_message(const shared_ptr<vsomeip::message>& response)
  {
    shared_ptr<vsomeip::payload> its_payload = response->get_payload();
    vsomeip::length_t l = its_payload->get_length();

    // Get payload
    stringstream ss;
    for(vsomeip::length_t i = 0; i < l; i++)
    {
      ss << setw(2) << setfill('0') << hex << (int)*(its_payload->get_data() + i) << " ";
    }

    cout << "Received message with Client/Session [" << setw(4) << setfill('0') << hex
         << _response->get_client() << "/" << setw(4) << setfill('0') << hex
         << _response->get_session() << "] " << ss.str() << endl;

    message_received = true;

    stop();
  }

  void on_availability(vsomeip::service_t _service, vsomeip::instance_t _instance,
                       bool _is_available)
  {
    cout << "CLIENT: Service [" << setw(4) << setfill('0') << hex << _service << "." << _instance
         << "] is " << (_is_available ? "available." : "NOT available.") << endl;

    if(_is_available)
      condition.notify_one();
  }

  // Client and server are in the same app. Start vsomeip,
  // send a message, receive it, and shut down vsomeip.
  TEST(vsomeip, one)
  {
    app = vsomeip::runtime::get()->create_application("Hello");
    app->init();
    app->register_availability_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, on_availability);
    app->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
    app->request_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
    app->register_message_handler(
      SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID,
      [](shared_ptr<vsomeip::message> message) { on_message(message); });
    sender = thread(send_message);
    app->start();

    ASSERT_TRUE(message_received);
  }
} // namespace
} // namespace pecomp
