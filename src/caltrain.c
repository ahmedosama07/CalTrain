#include <pthread.h>
#include "caltrain.h"



void
station_init(struct station *station)
{
	station->waitingPassengers = 0;
	station->onBoardPassengers = 0;
	pthread_mutex_init(&station->mutTrain, NULL);
	pthread_cond_init(&station->trainArrivedCond, NULL);
	pthread_cond_init(&station->trainFullCond, NULL);
}

void
station_load_train(struct station *station, int count)
{
	pthread_mutex_lock(&station->mutTrain);
	station->availableSeatsOnTrain = count;
	while (station->availableSeatsOnTrain > 0 && station->waitingPassengers > 0)
	{
		pthread_cond_broadcast(&station->trainArrivedCond);
		pthread_cond_wait(&station->trainFullCond, &station->mutTrain);
	}

	station->availableSeatsOnTrain = 0;
	pthread_mutex_unlock(&station->mutTrain);
}

void
station_wait_for_train(struct station *station)
{
	pthread_mutex_lock(&station->mutTrain);
	station->waitingPassengers++;
	while (station->onBoardPassengers == station->availableSeatsOnTrain)
	{
		pthread_cond_wait(&station->trainArrivedCond, &station->mutTrain);
	}
	station->onBoardPassengers++;
	station->waitingPassengers--;
	pthread_mutex_unlock(&station->mutTrain);
}

void
station_on_board(struct station *station)
{
	pthread_mutex_lock(&station->mutTrain);
	station->onBoardPassengers--;
	station->availableSeatsOnTrain--;
	if (station->availableSeatsOnTrain == 0 || (station->onBoardPassengers == 0 && station->waitingPassengers == 0))
	{
		pthread_cond_signal(&station->trainFullCond);
	}
	pthread_mutex_unlock(&station->mutTrain);
}
