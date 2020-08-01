#include <infiniband/fake_verbs.h>
#include <assert.h>

static struct ibv_context fake_dev_context;
static struct ibv_device fake_dev;
static struct ibv_device* fake_dev_list[] {
    NULL
};

struct ibv_context *ibv_open_device_fake(struct ibv_device *device) {
    assert(device == &fake_dev);

    // initialize device context


    return fake_dev_context;
}

int ibv_close_device_fake(struct ibv_context *context) {
    assert(context == &fake_dev_context);
}

const char *ibv_get_device_name_fake(struct ibv_device *device) {
    assert(device == &fake_dev);
    return "fakedev";
}

struct ibv_device **ibv_get_device_list_fake(int *num_devices) {
    if (num_devices != NULL) {
        *num_devices = 1;
    }

    fake_dev_list[0] = &fake_dev;
    return fake_dev_list;
}

void ibv_free_device_list_fake(struct ibv_device **list) {
    assert(list == fake_dev_list);
    // no-op
}


// assume only one port, though not possible
static struct ibv_port_attr fake_port_attr;

int ibv_query_port_fake(struct ibv_context *context, 
        uint8_t port_num, 
        struct ibv_port_attr *port_attr) {
    assert(context == &fake_dev_context);

    fake_port_attr.lid = 1;
    return &port_attr;
}

int ibv_query_gid_fake(struct ibv_context *context, 
        uint8_t port_num, 
        int index, 
        union ibv_gid *gid) {
    
}
