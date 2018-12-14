#ifndef SR_SERVER_H
#define SR_SERVER_H

/* import libraries */
/******************************************/
#include <vector>
#include <pthread.h>

#include "selective_repeat.h"
#include "../../../transport_packet/data_packet.h"
#include "../../transport_control/utilities/packet_window.h"
#include "../../../utilities/random_generator.h"


using namespace std;
#define PKT_LOSS_TIMEOUT 1 // in seconds
#define INIT_WIN_LEN 30

struct pkt_in{
    pkt_in() : status(NOT_SEND) {}
    PKT_STATUS status;
    time_t start_time;
};


/* class definition */
/******************************************/
class sr_server : public selective_repeat
{
private:
    // attributes
    vector<data_packet*> data_packets;
    vector<struct pkt_in> pkts_status;
    packet_window p_window;
    int implementation_done_flag = 0; // used to kick
    pthread_t send_id, recv_id;
    pthread_mutex_t print_lock;
    random_generator rg;

    // utility methods
    void send_packet(int index);
    static void* run_sender_thread(void *tmp);
    static void* run_receiver_thread(void *tmp);

    void send_handler();
    void recv_handler();

public:
    // constructor
    sr_server(port_handler *p);

    //interface methods
    void init(float plp, int seed, vector<data_packet*> &data_packets);
    void implement();
};

#endif 
