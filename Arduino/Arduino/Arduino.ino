#include <EEPROM.h>

#define COMMUNICATION_TYPE_DETECTION      0
#define COMMUNICATION_TYPE_QUERY          1
#define COMMUNICATION_TYPE_COMMAND        2
#define COMMUNICATION_TYPE_STATE_REQUEST  3

#define DRAWING_ROOM	0
#define LIVING_ROOM	1
#define BED_ROOM	2
#define STUDY		3

#define LIVING_LIGHT1	0
#define LIVING_LIGHT2	1
#define LIVING_FAN      2

#define DRAWING_ROOM_LIGHT_PIN	40  //50
#define LIVING_ROOM_LIGHT1_PIN	48
#define LIVING_ROOM_LIGHT2_PIN	46
#define STUDY_LIGHT_PIN	        44
#define BED_ROOM_LIGHT_PIN	42
#define FAN_PIN	                40  //40

#define EEPROM_CHECK_VALUE 	((int)(sizeof(houseState)))


struct ModelState
{
  byte	drawingLight;
  byte	livingLight1;
  byte  livingLight2;
  byte	bedLight;
  byte	studyLight;
  byte	fan;
}
houseState;


void setup()
{
  pinMode(DRAWING_ROOM_LIGHT_PIN, OUTPUT);
  pinMode(LIVING_ROOM_LIGHT1_PIN, OUTPUT);
  pinMode(LIVING_ROOM_LIGHT2_PIN, OUTPUT);
  pinMode(BED_ROOM_LIGHT_PIN, OUTPUT);
  pinMode(STUDY_LIGHT_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  houseState.drawingLight = 0;
  houseState.livingLight1 = 0;
  houseState.livingLight2 = 0;
  houseState.bedLight = 0;
  houseState.studyLight = 0;
  houseState.fan = 0;

  digitalWrite(DRAWING_ROOM_LIGHT_PIN, LOW);
  digitalWrite(LIVING_ROOM_LIGHT1_PIN, LOW);
  digitalWrite(LIVING_ROOM_LIGHT2_PIN, LOW);
  digitalWrite(BED_ROOM_LIGHT_PIN, LOW);
  digitalWrite(STUDY_LIGHT_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);

  Serial.begin(9600);
  Serial1.begin(9600);
  Serial1.setTimeout(9000);
}

void serialEvent1()
{
  byte buffer[64];
  if (Serial1.available())
  {
    byte bytesRead = Serial1.readBytesUntil('\n', buffer, 64);
    buffer[bytesRead] = 0;
    UpdateHouseState(buffer, bytesRead);
  }
}

void UpdateHouseState(byte buffer[], byte bytesRead)
{
  byte pin = -1;
  byte room;
  byte connection;
  byte state;

  String roomName;
  GetCommandDetailsFromString(buffer, bytesRead, &roomName, &connection, &state);
  /*Serial.println(roomName);
  Serial.println(connection);
  Serial.println(state);*/

  room = GetRoom(roomName);
  switch (room)
  {
    case DRAWING_ROOM:
      pin = DRAWING_ROOM_LIGHT_PIN;
      houseState.drawingLight = state;
      break;

    case LIVING_ROOM:
      switch (connection)
      {
        case LIVING_LIGHT1:
          pin = LIVING_ROOM_LIGHT1_PIN;
          houseState.livingLight1 = state;
          break;

        case LIVING_LIGHT2:
          pin = LIVING_ROOM_LIGHT2_PIN;
          houseState.livingLight2 = state;
          break;

        case LIVING_FAN:
          pin = FAN_PIN;
          houseState.fan = state;
          break;
      }
      break;

    case BED_ROOM:
      pin = BED_ROOM_LIGHT_PIN;
      houseState.bedLight = state;
      break;

    case STUDY:
      pin = STUDY_LIGHT_PIN;
      houseState.studyLight = state;
      break;
  }

  if (pin != -1)
  {
    digitalWrite(pin, state);
    //SaveState();
  }
  else
  {
    digitalWrite(13, LOW);
    delay(500);
    digitalWrite(13, HIGH);
  }
}

void GetCommandDetailsFromString(byte buffer[], byte length, String* room, byte* connection, byte* state)
{
  Serial.write(buffer, length);
  Serial.println("");
  *room = "";
  *connection = 0;
  byte i = 0;
  while (buffer[i] != ' ' && i < length)
  {
    *room += (char)buffer[i++];
  }

  i++;
  if (i < length)
  {
    *connection = buffer[i++] - '0';
  }

  i++;
  if (i < length)
  {
    *state = (buffer[i] == '1');
  }
}

byte GetRoom(String roomName)
{
  if (roomName.equalsIgnoreCase("drawingroom"))
  {
    return DRAWING_ROOM;
  }
  else if (roomName.equalsIgnoreCase("livingroom"))
  {
    return LIVING_ROOM;
  }
  else if (roomName.equalsIgnoreCase("bedroom"))
  {
    return BED_ROOM;
  }
  else if (roomName.equalsIgnoreCase("study"))
  {
    return STUDY;
  }
  return -1;
}

void loop()
{

}
