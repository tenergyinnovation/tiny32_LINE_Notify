/***********************************************************************
 * Project      :     tiny32_LINE_Notify
 * Description  :     Line Notify Test
 * Hardware     :     tiny32_v3
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     31/10/2024
 * Revision     :     1.0
 * Rev1.0       :     Origital
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     uten.boonliam@tenergyinnovation.co.th
 * TEL          :     +66 89 140-7205
 ***********************************************************************/
#include <Arduino.h>
#include <ArtronShop_LineNotify.h>
#include <tiny32_v3.h>
#include <esp_task_wdt.h>

#define SSID "XXXXXXXX"                                       // ใส่ ชื่อ Wifi ที่จะเชื่อมต่อ
#define PASSWORD "XXXXXXXXXXX"                                // ใส่ รหัส Wifi
#define LINE_TOKEN "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"  // ใส่ รหัส TOKEN ที่ได้มาจากข้างบน

/**************************************/
/*          Firmware Version          */
/**************************************/
String version = "0.1";

/**************************************/
/*          Header project            */
/**************************************/
void header_print(void)
{
    Serial.printf("\r\n***********************************************************************\r\n");
    Serial.printf("* Project      :     tiny32_LINE_Notify\r\n");
    Serial.printf("* Description  :     Line Notify Test\r\n");
    Serial.printf("* Hardware     :     tiny32_v3\r\n");
    Serial.printf("* Author       :     Tenergy Innovation Co., Ltd.\r\n");
    Serial.printf("* Date         :     31/10/2024\r\n");
    Serial.printf("* Revision     :     %s\r\n", version);
    Serial.printf("* Rev1.0       :     Origital\r\n");
    Serial.printf("* website      :     http://www.tenergyinnovation.co.th\r\n");
    Serial.printf("* Email        :     uten.boonliam@tenergyinnovation.co.th\r\n");
    Serial.printf("* TEL          :     +66 89 140-7205\r\n");
    Serial.printf("***********************************************************************/\r\n");
}

/**************************************/
/*        define object variable      */
/**************************************/
tiny32_v3 mcu;

/**************************************/
/*            GPIO define             */
/**************************************/

/**************************************/
/*       Constand define value        */
/**************************************/
// 10 seconds WDT
#define WDT_TIMEOUT 10

/**************************************/
/*       eeprom address define        */
/**************************************/

/**************************************/
/*        define global variable      */
/**************************************/

/**************************************/
/*           define function          */
/**************************************/

/***********************************************************************
 * FUNCTION:    setup
 * DESCRIPTION: setup process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void setup()
{
    Serial.begin(115200);
    header_print();

    Serial.println("Configuring WDT...");
    esp_task_wdt_init(WDT_TIMEOUT, true); // enable panic so ESP32 restarts
    esp_task_wdt_add(NULL);

    WiFi.begin(SSID, PASSWORD);
    Serial.printf("WiFi connecting to %s\n", SSID);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(400);
    }
    Serial.printf("\nWiFi connected\nIP : ");
    Serial.println(WiFi.localIP());

    // กำหนด Line Token
    LINE.setToken(LINE_TOKEN);
    LINE.send("Hello World");

    mcu.buzzer_beep(2);
}

/***********************************************************************
 * FUNCTION:    loop
 * DESCRIPTION: loop process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void loop()
{
    if (mcu.Sw1())
    {
        mcu.buzzer_beep(1);
        while (mcu.Sw1())
            ;
        LINE.send("Button SW1 Pressing");
        Serial.println("Button SW1 Pressing");
    }

    if (mcu.Sw2())
    {
        mcu.buzzer_beep(2);
        while (mcu.Sw2())
            ;
        LINE.send("Button SW2 Pressing");
        Serial.println("Button SW2 Pressing");
    }
    esp_task_wdt_reset();
    vTaskDelay(100);
}
