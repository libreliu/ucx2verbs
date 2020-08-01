#include <infiniband/fake_verbs.h>
#include <assert.h>

static struct ibv_context fake_dev_context;
static struct ibv_device fake_dev;
static struct ibv_pd fake_pd;
static struct ibv_device* fake_dev_list[] = {
    NULL
};
static struct ibv_cq fake_cq;

static struct ibv_mr* fake_mr_list = NULL;
static int fake_mr_list_len = 0;

struct ibv_context *ibv_open_device_fake(struct ibv_device *device) {
    assert(device == &fake_dev);

    // initialize device context
    return &fake_dev_context;
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
    gid->global.interface_id = 1;
    gid->global.subnet_prefix = 1;
    return 0;
}

// that is, reflecting to mem window of some kind..
struct ibv_pd *ibv_alloc_pd_fake(struct ibv_context *context) {
    assert(context == &fake_dev_context);
    return &fake_pd;
}

int ibv_dealloc_pd_fake(struct ibv_pd *pd) {
    assert(pd == &fake_pd);
    return 0;
}

struct ibv_mr *ibv_reg_mr_fake(struct ibv_pd *pd, void *addr, size_t length, int access) {
    if (fake_mr_list_len == 0) {
        fake_mr_list = (struct ibv_mr *)malloc(sizeof(struct ibv_mr));
        fake_mr_list[0].addr = addr;
        fake_mr_list[0].length = length;
    } else {
        struct ibv_mr *tmp = (struct ibv_mr *)malloc(sizeof(struct ibv_mr) * (fake_mr_list_len+1));
        for (int i = 0; i < fake_mr_list_len; i++) {
            tmp[i] = fake_mr_list[i];
        }
        tmp[fake_mr_list_len].addr = addr;
        tmp[fake_mr_list_len].length = length;
        free(fake_mr_list);
        fake_mr_list = tmp;
    }

    fake_mr_list_len++;
    return &fake_mr_list[fake_mr_list_len - 1];
}


struct ibv_comp_channel *ibv_create_comp_channel_fake(struct ibv_context *context) {
    // no-op if no cq notify involved
}

int ibv_destroy_comp_channel_fake(struct ibv_comp_channel *channel) {
    // no-op if no cq notify involved
}

int ibv_dereg_mr_fake(struct ibv_mr *mr) {
    // no-op
}

struct ibv_cq *ibv_create_cq_fake(struct ibv_context *context, int cqe, void *cq_context, struct ibv_comp_channel *channel, int comp_vector) {
    // completion queue, only one supported at this time
    static bool created = false;
    assert(!created);

    // todo: use context as the queue

    return &fake_cq;
}

int ibv_destroy_cq_fake(struct ibv_cq *cq) {
    // no-op, todo
}

int ibv_poll_cq_fake(struct ibv_cq *cq, int num_entries, struct ibv_wc *wc) {
    
}

int ibv_req_notify_cq_fake(struct ibv_cq *cq, int solicited_only) {

}


