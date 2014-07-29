#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <uv.h>

uv_loop_t *loop;
uv_udp_t send_socket;
uv_udp_t recv_socket;

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    buf->base = (char*) malloc(suggested_size);
    buf->len = suggested_size;
}

void on_send(uv_udp_send_t *req, int status) {
    fprintf(stdout, "on_send callback called!\n");

    if (status == -1) {
        fprintf(stderr, "Send error %s\n", uv_strerror(status));
        return;
    }
}

void on_read(uv_udp_t *req, ssize_t nread, const uv_buf_t*  buf, const struct sockaddr *addr, unsigned flags) {
    if (nread == -1) {
        fprintf(stderr, "Read error!\n");
        uv_close((uv_handle_t*) req, NULL);
        free(buf->base);
        return;
    }

    char sender[17] = { 0 };
    uv_ip4_name((struct sockaddr_in*) addr, sender, 16);
    fprintf(stderr, "Recv from %s\n", sender);

    uv_udp_recv_stop(req);
}

int main() {
    loop = uv_default_loop();


    uv_udp_init(loop, &recv_socket);

    char recv_addr[sizeof(struct sockaddr_in6)];
    uv_ip4_addr("127.0.0.1", 4242, (struct sockaddr_in*)&recv_addr);
    uv_udp_bind(&recv_socket, (struct sockaddr*)&recv_addr, 0);
    uv_udp_recv_start(&recv_socket, alloc_buffer, on_read);

    uv_udp_send_t send_req;
    uv_buf_t buffer = uv_buf_init(malloc(1), 0);

    uv_udp_init(loop, &send_socket);

    char send_addr[sizeof(struct sockaddr_in6)];
    uv_ip4_addr("127.0.0.1", 4242, (struct sockaddr_in*)&send_addr);
    uv_udp_send(&send_req, &send_socket, &buffer, 1, (struct sockaddr*)send_addr, on_send);

    return uv_run(loop, UV_RUN_DEFAULT);
}
