# os-course-work
rootik for hiding processes and its sockets

# implementation
Processes are hidden by khooking getdents() and getdents64();

Process's sockets are hidden by khooking tcp & upd seq_show() funcs, where we looking for matching process file inode and socket's inode
