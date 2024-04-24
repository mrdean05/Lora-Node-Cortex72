#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "../../src/include/lorawan.h"

#include "config.h"


// OTAA settings
const struct lorawan_otaa_settings otaa_settings = {
    .device_eui   = LORAWAN_DEVICE_EUI,
    .app_eui      = LORAWAN_APP_EUI,
    .app_key      = LORAWAN_APP_KEY,
    .channel_mask = LORAWAN_CHANNEL_MASK
};

// variables for receiving data
int receive_length = 0;
uint8_t receive_buffer[242];
uint8_t receive_port = 0;

int main(void)
{
    printf("LoRaWAN - Hello OTAA\n");

    printf("Initializing LoRaWAN....\n");

    if (lorawan_init_otaa(LORAWAN_REGION, &otaa_settings) < 0) {
        printf("failed!!!\n");
        return 0;
    } else {
        printf("success!!!!\n");
    }
 
     
    //Start the join process and wait
    printf("Joining the LoRaWAN network\n");
    lorawan_join();

    printf("Waiting to Join\n");

    while (!lorawan_is_joined())
    {
        lorawan_process();
        //printf("Delay\n");
        //usleep(100 * 1000);

    }
    printf("Joined successfully!\n");

     time_t last_message_time = time(NULL);

    while (1)
    {
        // let the lorwan library process pending events
        lorawan_process();

        //Work on this timer
        // get the current time and see if 5 seconds have passed
        // since the last message was sent
        //Needs attention
        time_t now = time(NULL);

        if ((now - last_message_time) > 5) {
            const char* message = "hello world!";

            // try to send an unconfirmed uplink message
            printf("sending unconfirmed message '%s' ... ", message);
            if (lorawan_send_unconfirmed(message, strlen(message), 2) < 0) {
                printf("failed!!!\n");
            } else {
                printf("success!\n");
            }

            last_message_time = now;
        }

        // check if a downlink message was received
        receive_length = lorawan_receive(receive_buffer, sizeof(receive_buffer), &receive_port);
        if (receive_length > -1) {
            printf("received a %d byte message on port %d: ", receive_length, receive_port);

            for (int i = 0; i < receive_length; i++) {
                printf("%02x", receive_buffer[i]);
            }
            printf("\n");
        }
    }

}