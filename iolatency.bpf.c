struct tp_args {
    u64 __unused__;
    dev_t dev;
    sector_t sector;
    unsigned int nr_sector;
    unsigned int bytes;
    char rwbs[8];
    char comm[16];
    char cmd[];
};

struct start_key {
    dev_t dev;
    sector_t sector;
};

BPF_HASH(start, struct start_key);
BPF_HISTOGRAM(block_io_latencies);

int handle_block_rq_issue(struct tp_args *args) {
    bpf_trace_printk("BPF triggered handle_block_rq_issue.\n");

    struct start_key key = {
        .dev = args->dev,
        .sector = args->sector
    };

    u64 ts = bpf_ktime_get_ns();
    start.update(&key, &ts);
    return 0;
}

int handle_block_rq_complete(struct tp_args *args) {
    bpf_trace_printk("BPF triggered handle_block_rq_complete.\n");

    struct start_key key = {
        .dev = args->dev,
        .sector = args->sector
    };

    u64 *tsp, delta;
    tsp = start.lookup(&key);

    if (tsp == 0) {
        return 0;   // missed issue
    }

    delta = (bpf_ktime_get_ns() - *tsp) / 1000; // convert to microseconds

    block_io_latencies.atomic_increment(bpf_log2l(delta));

    start.delete(&key);
    return 0;
}
