#include <pthread.h>
#include "caltrain.h"



void
station_init(struct station *station)
{
	station->waitingPassengers = 0;
	station->availablePlacesOnTrain = 0;
	pthread_mutex_init(&station->mutTrain, NULL);
	pthread_cond_init(&station->trainArrivedCond, NULL);
	pthread_cond_init(&station->trainFullCond, NULL);
}

void
station_load_train(struct station *station, int count)
{
	pthread_mutex_lock(&station->mutTrain);
	station->availablePlacesOnTrain = 2 * count;													// Board then sit
	pthread_cond_signal(&station->trainArrivedCond);
	while (station->availablePlacesOnTrain > 0 && station->waitingPassengers > 0)
	{
		pthread_cond_wait(&station->trainFullCond, &station->mutTrain);
	}

	station->availablePlacesOnTrain = 0;
	pthread_mutex_unlock(&station->mutTrain);
}

void
station_wait_for_train(struct station *station)
{
	pthread_mutex_lock(&station->mutTrain);
	station->waitingPassengers++;
	while ((station->availablePlacesOnTrain % 2 == 1) || station->availablePlacesOnTrain == 0)		// Wait for places to board and sit
	{
		pthread_cond_wait(&station->trainArrivedCond, &station->mutTrain);
	}
	station->availablePlacesOnTrain--;
	pthread_mutex_unlock(&station->mutTrain);
}

void
station_on_board(struct station *station)
{
	pthread_mutex_lock(&station->mutTrain);
	station->waitingPassengers--;
	station->availablePlacesOnTrain--;
	if (station->availablePlacesOnTrain == 0 || station->waitingPassengers == 0)
	{
		pthread_cond_signal(&station->trainFullCond);
	}
	pthread_cond_signal(&station->trainArrivedCond);
	pthread_mutex_unlock(&station->mutTrain);
}
