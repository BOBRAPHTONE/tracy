#ifndef __SIM900_H__
#define __SIM900_H__

#include "proj.h"

#define SIM900_DTR_HIGH         P1OUT |= BIT3
#define SIM900_DTR_LOW          P1OUT &= ~BIT3
#define SIM900_RTS_HIGH         P1OUT |= BIT6
#define SIM900_RTS_LOW          P1OUT &= ~BIT6
#define SIM900_PWRKEY_HIGH      P1OUT &= ~BIT7
#define SIM900_PWRKEY_LOW       P1OUT |= BIT7
#define SIM900_VBAT_ENABLE      P2OUT |= BIT0
#define SIM900_VBAT_DISABLE     P2OUT &= ~BIT0

#define SIM900_CTS              BIT5
#define SIM900_CTS_IN           P1IN & BIT5
#define SIM900_UCAIFG           UCA1IFG
#define SIM900_UCATXBUF         UCA1TXBUF

// states that can be reached by the state machine
typedef enum {
    SIM900_ON,
    SIM900_OFF,
    SIM900_PWRKEY_ACT,
    SIM900_VBAT_ON,
    SIM900_PRE_IDLE,
    SIM900_IDLE,
    SIM900_AT,
    SIM900_WAITREPLY,
    SIM900_VBAT_OFF,
    SIM900_SET1,
    SIM900_TEXT_INPUT,
    SIM900_TEXT_RCVD,
    SIM900_IP_INITIAL,
    SIM900_IP_START,
    SIM900_IP_GPRSACT,
    SIM900_IP_STATUS,
    SIM900_IP_CONNECT,
    SIM900_IP_CONNECT_OK,
    SIM900_IP_SEND,
    SIM900_IP_PUT,
    SIM900_IP_CLOSE,
    SIM900_IP_SHUT
} sim900_state_t;

// commands that are compatible with the state machine
typedef enum {
    CMD_NULL,
    CMD_ON,
    CMD_OFF,
    CMD_FIRST_PWRON,
    CMD_SEND_SMS,
    CMD_SEND_GPRS
} sim900_cmd_t;

// command type
typedef enum {
    CMD_UNSOLICITED,
    CMD_SOLICITED,
} sim900_cmd_type_t;

// return codes
typedef enum {
    RC_NULL,
    RC_OK,
    RC_ERROR,
    RC_TMOUT,
    RC_TEXT_INPUT,
    RC_CMGS,
    RC_STATE_IP_INITIAL,
    RC_STATE_IP_START,
    RC_STATE_IP_GPRSACT,
    RC_STATE_IP_STATUS,
    RC_STATE_IP_CONNECT,
    RC_STATE_IP_SHUT
} sim900_rc_t;

typedef enum {
    TTY_NULL,
    TTY_RX_PENDING,
    TTY_RX_WAIT
} sim900_tty_t;


#define RDY         BIT0
#define CALL_RDY    BIT1

struct sim900_t {
    uint8_t checks;
    uint8_t rdy;
    sim900_cmd_t cmd;
    sim900_cmd_type_t cmd_type;
    sim900_rc_t  rc;
    sim900_state_t next_state;
    sim900_tty_t console;
};

struct sim900_t sim900;

void sim900_init(void);
void sim900_init_messagebus(void);
void sim900_first_pwron(void);
void sim900_halt(void);
void sim900_send_fix_sms(void);
void sim900_send_fix_gprs(void);

uint16_t sim900_tx_str(char *str, const uint16_t size);
uint8_t sim900_tx_cmd(char *str, const uint16_t size, const uint16_t reply_tmout);
uint8_t sim900_parse_rx(char *str, const uint16_t size);

#endif
