#include <pthread.h>

struct station {
	int waitingPassengers;
	int onBoardPassengers;
	int availableSeatsOnTrain;
	pthread_mutex_t mutTrain;
	pthread_cond_t trainArrivedCond;
	pthread_cond_t trainFullCond;
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);