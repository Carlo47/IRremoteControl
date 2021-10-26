# IRremoteControl
The program uses the IRremote library to explore the codes
of your infrared remote control. The codes for 4 different
remote controls are stored in a table which you can complete
with your own codes.

Each time a button is pressed, the table is searched for the
decoded command and the assigned action is executed.

## Parts
The IR receiver breakout is from a sensor kit for Arduino

![IRreceiver](images/IRreceiverBreakout.jpg)

## Wiring

```
  IR Receiver               Arduino UNO 
.-------------.           .---------------
|             |           | 
| .---.     Y o---------> o 11
| | X |     R o---------> o 5V
| `---´     G o---------> o GND
|             |           |
`-------------´           `---------------
```

## TOSHIBA TV CT-90404 NEC Protocol 
```
.------------------------------.
|           on/off             |
|            0x12              |
|      0x14        0x44        |
|   0x11  0x59  0x13  0x0C     |
|                              |
|      0x01  0x02  0x03        |          1  2  3
|      0x04  0x05  0x06        |          4  5  6       
|      0x07  0x08  0x09        |          7  8  9
|      0x62  0x00  0x52        |         AD  0  <->  
|                              |
|      0x1A  0x16  0x1B        |
|      ||||  0x10  ||||        | 
|      0x1E  0x63  0x1F        |
|                              |
|   0xDA  0x66  0x17  0x47     |
|                              |
|            0x73              |
|      0x5B  0x19  0x45        |
|                              |
|  <<    <     OK    >     >>  |
| 0x75  0x42  0x21  0x40  0x76 |
|                              |
|       0x64  0x1D  0x43       |
|             0x74             |
|                              |
|       0x53  0x67  0x0D       |
|    0x54  0x68  0x6A  0x15    |
|    0x48  0x49  0x4A  0x4B    |
|          0x22  0x6F          |
`------------------------------´
```

## ACER RC6 Protocol 
```
.----------------------------.
|                    on/off  |
|                     0x0C   |
|   0x46  0x47  0x49  0x4A   |
|            0x19            |
|      0x17        0x18      |
|    0x15    0x16    0x14    |
|        0x1B    0x1A        |
|   0x23     0x1E     0x0F   |
|      0x20  0x22  0x21      |
|            0x1F            |
|   0x10              0x12   |
|    \\\     0x0D     ///    |
|    0x11            0x13    |
|            0x0E            |
|   0x48  0x26  0x25  0x24   |
|                            |
|      0x01  0x02  0x03      |          1  2  3
|      0x04  0x05  0x06      |          4  5  6       
|      0x07  0x08  0x09      |          7  8  9
|      0x1D  0x00  0x1C      |          *  0  #  
|                            |
|        0x0A    0x0B        |
|   0x5B  0x5C  0x5D  0x5E   |
|             0x5A           |
`----------------------------´
```

## NONAME RC5 Protocol 

```
.----------------------------.
|   SPKR             on/off  |
|   0x0D              0x0C   |
|                            |
|      0x01  0x02  0x03      |          1  2  3
|      0x04  0x05  0x06      |          4  5  6       
|      0x07  0x08  0x09      |          7  8  9
|      0x2C  0x00  0x2A      |        EPG  0  LIST  
|                            |
|            0x4E            |
|      0x2F        0x45      |
|            0x20            |
|   0x11     0x57     0x10   |
|            0x21            |
|   0x2D              0x22   |
|            0x52            |
|                            |
|   0x30  0x3C  0x23  0x40   |
|   0x31  0x38  0x39  0x41   |
|                            |
|   0x53     0x55     0x46   |
|                            |
|   0x54  0x35  0x58  0x56   |
|   0x37  0x36  0x32  0x34   |
`----------------------------´
```