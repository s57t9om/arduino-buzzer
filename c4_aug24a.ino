const int numrow = 4;
const int numcol = 4;
const char arrange[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
const int rowpin[4] = {13, 12, 11, 10};
const int colpin[4] = {9, 8, 7, 6};
const int staytime = 1;
char key;
char a;

char getkey() {
    for (int q = 0; q < 4; q++) {
        digitalWrite(colpin[q], LOW);
        for (int w = 0; w < 4; w++) {
            if (digitalRead(rowpin[w]) == LOW) {
                delay(staytime);
                while (digitalRead(rowpin[w]) == LOW) {
                    a = arrange[w][q];
                    return a;
                }
            }
        }
        digitalWrite(colpin[q], HIGH);
    }
    return 0;
}

void setup() {
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
    for (int q = 0; q < 4; q++) {
        pinMode(rowpin[q], INPUT);
        digitalWrite(rowpin[q], HIGH);
    }
    for (int q = 0; q < 4; q++) {
        pinMode(colpin[q], OUTPUT);
        digitalWrite(colpin[q], HIGH);
    }
    Serial.begin(9600);
}

float sum;
int b;

void loop() {
    bool isclose = false;

    a = getkey();
    if (a == 'A') {
        for (int q = 0; q <= 22; q++) {
            a = getkey();
            if (a == 'B') {
                isclose = true;
                break;
            }

            b = ((-q / 3) * (-q / 3) * (-q / 3)) + 400;
            sum += b;
            digitalWrite(2, LOW);
            delay(b);
            digitalWrite(2, HIGH);
            delay(b);
        }

        a = getkey();
        if (a == 'B') {
            isclose = true;
        }

        if (isclose == false) {
            for (int q = 0; q < 10; q++) {
                a = getkey();
                if (a == 'B') {
                    isclose = true;
                    break;
                }
                digitalWrite(2, LOW);
                delay(b + 3);
                digitalWrite(2, HIGH);
                delay(b + 3);
            }

            a = getkey();
            if (a == 'B') {
                isclose = true;
            }

            if (isclose == false) {
                digitalWrite(2, LOW);
                delay(2000);
                digitalWrite(2, HIGH);
            }
        }

        Serial.print(sum * 2 / 1000);
        Serial.println('s');
        sum = 0;
    }
    isclose = false;
}