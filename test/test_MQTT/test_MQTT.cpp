#ifdef UNIT_TEST

#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <PubSubClient.h>
#include <unity.h>

#define TESTS_NUM 10
#define TESTS_DELAY 100

#define WIFI_SSID "NN"
#define WIFI_PASSWORD "clave"

#define MQTT_DEVICE "dut"
#define MQTT_HOST "192.168.12.2"
#define MQTT_PORT 1883
#define MQTT_TOPIC "smmrtest"

#ifdef DEBUG_ESP_PORT
#define INFO_ESP_PORT DEBUG_ESP_PORT
#else
#define INFO_ESP_PORT Serial
#endif
#define INFO_TEST(...)                  \
	INFO_ESP_PORT.print("INFO TEST: "); \
	INFO_ESP_PORT.printf(__VA_ARGS__)

WiFiClient wifi;
PubSubClient client(wifi);
    
void test_connect_wifi()
{
	bool ret = true;
	char counter = 0;

	INFO_TEST("Connecting to WIFI...\n");
	WiFi.disconnect();
    WiFi.mode(WIFI_STA);
	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		INFO_TEST("Trying reconnect to WIFI\n");
		if (counter == 5)
		{
			ret = false;
			break;
		}
		counter++;
	}
	TEST_ASSERT_TRUE(ret);
}

void test_connect_mqtt()
{
	bool ret = true;
	char counter = 0;

    Serial.print("Attempting MQTT connection...");
    String clientId = MQTT_DEVICE;
    client.setServer(MQTT_HOST, MQTT_PORT);
    // Attempt to connect
   	while (!client.connect(clientId.c_str()))
	{
		delay(500);
		INFO_TEST("Trying reconnect to MQTT\n");
		if (counter == 5)
		{
			ret = false;
			break;
		}
		counter++;
	}
    TEST_ASSERT_TRUE(ret);
}

void test_publish_mqtt()
{
    TEST_ASSERT_TRUE(client.publish("prueba/topic1", "hello world"));
}

void setup()
{
	// NOTE!!! Wait for >2 secs
	// if board doesn't support software reset via Serial.DTR/RTS
	delay(2000);
	
	UNITY_BEGIN(); // IMPORTANT LINE!
}

uint8_t i = 0;

void loop()
{
	if (i < TESTS_NUM)
	{
		INFO_TEST("Se conecta a Wifi\n");
		RUN_TEST(test_connect_wifi);

		INFO_TEST("Se chequea conección\n");
		RUN_TEST(test_connect_mqtt);
        
        INFO_TEST("Se chequea publicacion\n");
		RUN_TEST(test_publish_mqtt);

		delay(TESTS_DELAY);
		i++;
	}
	else
	{
		UNITY_END(); // stop unit testing
	}
}

#endif
