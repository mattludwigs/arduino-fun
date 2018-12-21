#define ADD 0x00
#define SUB 0x01

const int debounce_delay = 50;
int counter = 0;
unsigned long last_debounce_time = 0;

struct button {
  int pin_number;
  int state;
  int prev_state;
};

struct button inc_btn = { .pin_number = 2, .state = HIGH, .prev_state = HIGH };
struct button dec_btn = { .pin_number = 12, .state = HIGH, .prev_state = HIGH };

void update_counter(int op) {
  switch (op) {
    case ADD:
      counter++;
      break;
    case SUB:
      counter--;
      break;
  }
}

void handle_btn_push(struct button *btn, int op) {
  int btn_read = digitalRead(btn->pin_number);

  if (btn_read != btn->prev_state) {
    last_debounce_time = millis();
  }

  if (millis() > (last_debounce_time + debounce_delay)) {
    if (btn_read != btn->state) {
      btn->state = btn_read;

      if (btn->state == LOW) {
        update_counter(op);
        Serial.println(counter);
      }
    }
  }

  btn->prev_state = btn_read;
}

void setup() {
  pinMode(inc_btn.pin_number, INPUT_PULLUP);
  pinMode(dec_btn.pin_number, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  handle_btn_push(&inc_btn, ADD);
  handle_btn_push(&dec_btn, SUB);
}
