
/*Declare data*/
#define DELAY 100000

uint8_t map[512];

/*Declare display related functions*/
uint8_t spi_send_recv(uint8_t data);
void display_init();
void display_update();
void toggle_pixel(int *x, int *y, bool on);
bool is_pixel_on(int x, int y);

/*Declare other functions*/
void delay(int cyc);
int getbtn(int x);
int getsw(int x);
