# UCX2Verbs

## Dev
1. Finding the right structs by `/enum [A-Za-z_]+ {.*};/gmsU` and `/struct [A-Za-z_]+ {.*};/gmsU` respectively
   - `/struct [A-Za-z_]+;/gmsU` for some placeholders
   - `/enum {.*};/gmsU` for some anonymous enums
2. one completion queue, one pd, a mr list and so on

## Slide Info

Title: Attempts on bridging UCP to ibVerbs

NVMf/NVMe -> verbs2ucp -> ucp -> ibverbs

It's a silly idea, since UCP it self is built on top of libibverbs and so many others, and the only advantage I could think of is that it stays in rule.

As we advance we've encountered several problems:
1. The namespace conflict
   - Ideas on resolving this: Add "_fake" for all functions first, then replace syms on corresponding files, or to use some linking techniques, like editing all syms in object file (but further problems will arise, such as DWARF symbols)
2. Layer of abstractions
   - In simple Verbs applications (e.g. the one with only send/recv), wrapping to ucp is trivial
   - In complicated ones, wrap like following:
      - Atomics <-> ucp_atomic_*
      - RDMA Read / Write <-> ucp_get_nb / ucp_put_nb
      - Send/Recv <-> ucp_tag_send_nb / ucp_tag_recv_nb
   - However, we probably don't have that kind of familiarity to deal with UCP and ibVerbs to that extent, since making the above scheme work requires fair knowledge in their API's respectively.
      - Especially on the pd and the mr stuff.. Those are the things that we're not that familiar with.

We've written some code and tried reading the InfiniBand Architecture Manual on the translation scheme we strive to use, but we then dropped this idea.  Also, we are quite bothered where will it be used if we've truly written our "verbs to ucx" library.



## Fakes
```
int ibv_query_port(struct ibv_context *context, uint8_t port_num, struct ibv_port_attr *port_attr);
struct ibv_context *ibv_open_device(struct ibv_device *device);
int ibv_close_device(struct ibv_context *context);
const char *ibv_get_device_name(struct ibv_device *device);
struct ibv_device **ibv_get_device_list(int *num_devices);
void ibv_free_device_list(struct ibv_device **list);
int ibv_query_gid(struct ibv_context *context, uint8_t port_num, int index, union ibv_gid *gid);
struct ibv_comp_channel *ibv_create_comp_channel(struct ibv_context *context);
int ibv_destroy_comp_channel(struct ibv_comp_channel *channel);
struct ibv_pd *ibv_alloc_pd(struct ibv_context *context);
int ibv_dealloc_pd(struct ibv_pd *pd);
struct ibv_mr *ibv_reg_mr(struct ibv_pd *pd, void *addr, size_t length, int access);
int ibv_dereg_mr(struct ibv_mr *mr);
struct ibv_cq *ibv_create_cq(struct ibv_context *context, int cqe, void *cq_context, struct ibv_comp_channel *channel, int comp_vector);
int ibv_destroy_cq(struct ibv_cq *cq);
int ibv_poll_cq(struct ibv_cq *cq, int num_entries,
struct ibv_wc *wc);
struct ibv_qp *ibv_create_qp(struct ibv_pd *pd, struct ibv_qp_init_attr *qp_init_attr);
int ibv_modify_qp(struct ibv_qp *qp, struct ibv_qp_attr *attr, int attr_mask);
int ibv_destroy_qp(struct ibv_qp *qp);
int ibv_req_notify_cq(struct ibv_cq *cq, int solicited_only);
int ibv_post_send(struct ibv_qp *qp, struct ibv_send_wr *wr, struct ibv_send_wr **bad_wr);
int ibv_post_recv(struct ibv_qp *qp, struct ibv_recv_wr *wr, struct ibv_recv_wr **bad_wr);
```