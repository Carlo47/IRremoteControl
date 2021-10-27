/**
 * Program      IRremoteControl.cpp
 * Author       2021-10-26 Charles Geiser (https://www.dodeka.ch)
 * 
 * Purpose      The program uses the IRremote library to explore the codes
 *              of your infrared remote control. The codes for 4 different
 *              remote controls are stored in a table which you can complete
 *              with your own codes.
 *
 *              Each time a button is pressed, the table is searched for the
 *              decoded command and the assigned action is executed. 
 * 
 * Board        Arduino UNO
 *
 * Wiring
 *                IR Receiver               Arduino UNO 
 *              .-------------.           .--------------
 *              |             |           | 
 *              | .---.     Y o---------> o 11
 *              | | X |     R o---------> o 5V
 *              | `---´     G o---------> o GND
 *              |             |           |
 *              `-------------´           `--------------
 *
 * Remarks      The IR receiver breakout is from a sensor kit for the Arduino
 *
 * References
 */
#include <Arduino.h>
#include <IRremote.h>

#define PIN_IR_RECEIVE  11

// Add your IR Controller
enum class RemoteController {TOSHIBA_NEC, NONAME_RC5, ACER_RC6, TERRATEC_NEC};

typedef void (*Action)(const uint8_t cmd);
typedef struct { const uint8_t cmd[4]; const char *txt; Action action; } Command;

// Forward declarations
void _nop(const uint8_t i) {};
void showCmd(uint8_t cmd);
void toggleLed(uint8_t cmd);
void selectIRcontrol(uint8_t cmd);

// Select one of the defined controllers
RemoteController remoteCtrl = RemoteController::TOSHIBA_NEC;

// Add the commands of our IR control, do not forget to adjust the array size in typedef Command
// Replace the action showCmd with your own function that should execute a command.
const Command cmdTbl[] = 
{ // TOSHIBA  NONAME   ACER  TERRATEC
    { {0x00,   0x00,   0x00,  0x00}, "0", selectIRcontrol } ,
    { {0x01,   0x01,   0x01,  0x01}, "1", selectIRcontrol } ,
    { {0x02,   0x02,   0x02,  0x02}, "2", selectIRcontrol } ,
    { {0x03,   0x03,   0x03,  0x03}, "3", selectIRcontrol } ,
    { {0x04,   0x04,   0x04,  0x04}, "4", showCmd } ,
    { {0x05,   0x05,   0x05,  0x05}, "5", showCmd } ,
    { {0x06,   0x06,   0x06,  0x06}, "6", showCmd } ,
    { {0x07,   0x07,   0x07,  0x07}, "7", showCmd } ,
    { {0x08,   0x08,   0x08,  0x08}, "8", showCmd } ,
    { {0x09,   0x09,   0x09,  0x09}, "9", showCmd } ,
    { {0x21,   0x57,   0x22,  0x19}, "OK",showCmd } ,
    { {0x42,   0x11,   0x20,  0x17}, "<", showCmd } ,
    { {0x40,   0x10,   0x21,  0x18}, ">", showCmd } ,
    { {0x19,   0x20,   0x1E,  0x15}, "UP",     showCmd } ,
    { {0x1D,   0x21,   0x1F,  0x16}, "DOWN",   showCmd } ,
    { {0x75,   0x54,   0x15,  0x1C}, "<<",     showCmd } ,
    { {0x76,   0x56,   0x14,  0x1D}, ">>",     showCmd } ,
    { {0x1A,   0x40,   0x10,  0x0F}, "V-UP",   showCmd } ,
    { {0x1E,   0x41,   0x11,  0x10}, "V-DOWN", showCmd } ,
    { {0x1B,   0x30,   0x12,  0x0D}, "CH-UP",  showCmd } ,
    { {0x1F,   0x31,   0x13,  0x0E}, "CH-DOWN",showCmd } ,
    { {0x12,   0x0C,   0x0C,  0x0A}, "ON/OFF", toggleLed } ,
    { {0x48,   0x37,   0x5B,  0xFF}, "RED",    showCmd } ,
    { {0x49,   0x36,   0x5C,  0xFF}, "GREEN",  showCmd } ,
    { {0x4A,   0x32,   0x5D,  0xFF}, "YELLOW", showCmd } ,
    { {0x4B,   0x34,   0x5E,  0xFF}, "BLUE",   showCmd } ,
};
const int nbrCmds = sizeof( cmdTbl) / sizeof(cmdTbl[0]);

/**
 * Default action to be performed an any command
 */
void showCmd(const uint8_t i)
{
    char buf[32];
    snprintf(buf, sizeof(buf), "0x%X  %s", cmdTbl[i].cmd[(int)remoteCtrl], cmdTbl[i].txt);
    Serial.println(buf);
}

/**
 * Action to be performed on button press "ON/OFF"
 */
void toggleLed(const uint8_t cmd)
{
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

/**
 * Selects another controller by pushing buttons 0..3
 */
void selectIRcontrol(uint8_t cmd)
{
    switch (cmd)
    {
        case 0x00:
            remoteCtrl = static_cast<RemoteController>(cmd);
            Serial.println("TOSHIBA_NEC selected");
        break;
        case 0x01:
            remoteCtrl = static_cast<RemoteController>(cmd);
            Serial.println("NONAME_RC5 selected");
        break;
        case 0x02:
            remoteCtrl = static_cast<RemoteController>(cmd);
            Serial.println("ACER_RC6 selected");
        break;
        case 0x03:
            remoteCtrl = static_cast<RemoteController>(cmd);
            Serial.println("TERRATEC_NEC selected");
        break;
        default:
        break;  
    }                  
}

/**
 * Looks in the command table for the action to be performed 
 */
void doCommand(const uint8_t cmd)
{
    for (int i = 0; i < nbrCmds; i++)
    {
        if (cmd == cmdTbl[i].cmd[(int)remoteCtrl])
        {
            cmdTbl[i].action(i);
            break;
        }
    }
}

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    IrReceiver.begin(PIN_IR_RECEIVE, DISABLE_LED_FEEDBACK);
}

void loop() 
{
    if (IrReceiver.decode()) 
    {
        IrReceiver.printIRResultShort(&Serial);
        doCommand(IrReceiver.decodedIRData.command);
        IrReceiver.resume(); // Get ready for the next signal to decode
    }
    delay(200);
}