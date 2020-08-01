#ifndef UCX2VERBS_VERBS_H
#define UCX2VERBS_VERBS_H

#include "structures.h"

// --- device ---
struct ibv_context *ibv_open_device_fake(struct ibv_device *device);
int ibv_close_device_fake(struct ibv_context *context);
const char *ibv_get_device_name_fake(struct ibv_device *device);
struct ibv_device **ibv_get_device_list_fake(int *num_devices);
void ibv_free_device_list_fake(struct ibv_device **list);

// --- port ---
int ibv_query_port_fake(struct ibv_context *context, uint8_t port_num, struct ibv_port_attr *port_attr);

// --- gid ---
int ibv_query_gid_fake(struct ibv_context *context, uint8_t port_num, int index, union ibv_gid *gid);

// --- comp channel ---
struct ibv_comp_channel *ibv_create_comp_channel_fake(struct ibv_context *context);
int ibv_destroy_comp_channel_fake(struct ibv_comp_channel *channel);

// --- pd ---
struct ibv_pd *ibv_alloc_pd_fake(struct ibv_context *context);
int ibv_dealloc_pd_fake(struct ibv_pd *pd);

// --- mr ---
struct ibv_mr *ibv_reg_mr_fake(struct ibv_pd *pd, void *addr, size_t length, int access);
int ibv_dereg_mr_fake(struct ibv_mr *mr);

// --- cq ---
struct ibv_cq *ibv_create_cq_fake(struct ibv_context *context, int cqe, void *cq_context, struct ibv_comp_channel *channel, int comp_vector);
int ibv_destroy_cq_fake(struct ibv_cq *cq);
int ibv_poll_cq_fake(struct ibv_cq *cq, int num_entries, struct ibv_wc *wc);
int ibv_req_notify_cq_fake(struct ibv_cq *cq, int solicited_only);

// --- qp ---
struct ibv_qp *ibv_create_qp_fake(struct ibv_pd *pd, struct ibv_qp_init_attr *qp_init_attr);
int ibv_modify_qp_fake(struct ibv_qp *qp, struct ibv_qp_attr *attr, int attr_mask);
int ibv_destroy_qp_fake(struct ibv_qp *qp);

// --- send and recv ---
int ibv_post_send_fake(struct ibv_qp *qp, struct ibv_send_wr *wr, struct ibv_send_wr **bad_wr);
int ibv_post_recv_fake(struct ibv_qp *qp, struct ibv_recv_wr *wr, struct ibv_recv_wr **bad_wr);


#endif