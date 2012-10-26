void setup()
{
  for (int i = 0; i < 20; i++)
    pinMode(i, OUTPUT);
}

void loop()
{
  for (int layer = 0; layer < 4; layer++)
  {
    digitalWrite(layer,HIGH);
    for (int node = 4; node < 20; node++)
    {
      digitalWrite(node,HIGH);
      delay(100);
      digitalWrite(node,LOW);
    }
  }
}
