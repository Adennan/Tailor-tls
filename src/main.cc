

int main(int argc, char *argv[])
{
	EpollServer epoll;
	epoll.init(8080, 10);
	// epoll.init("127.0.0.1", 8080, 10);
	epoll.run(2000);
    return 0;
}