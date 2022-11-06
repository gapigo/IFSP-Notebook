#define N 100
#define TRUE 1
#define FALSE 0

void producer(void)
{
    int item;
    message m;

    while (TRUE) {
	produce_item(&item);
	receive(consumer, &m);
	build_message(&m, item);
	send(consumer, &m);	
    }
}

void consumer(void) {
    int item, i;
    message m;

    for(i = 0; i < N; i++) send(producer, &m);
    while(TRUE) {
  receive(producer, &m);
	extract_item(&m, &item);
	send(producer, &m);
	consume_item(item);
    }
}

