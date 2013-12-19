/*
 * QueueJobBuffer.h
 *
 *  Created on: Dec 18, 2013
 *      Author: Josiah
 */

#ifndef QUEUEJOBBUFFER_H_
#define QUEUEJOBBUFFER_H_

#include <iostream>
#include <sstream>
#include <queue>
#include "JobEvent.h"
#include "Debug.h"
#include "Accumulator.h"
#include "PriorityQueueJobSorter.h"

class QueueJobBuffer {
	std::queue<JobEventPtr> queue;
	double last_rejected_time;
	AccumulatorPtr time_between_rejected_jobs;
	PriorityQueueJobSorterPtr sortedJobQueue;
protected:
	virtual std::ostream& toStream(std::ostream& out);
public:
	const long max_size;

	QueueJobBuffer(
			long size,
			AccumulatorPtr time_between_rejected_jobs,
			PriorityQueueJobSorterPtr sortedJobQueue);
	virtual ~QueueJobBuffer() {
	}

	bool is_full();
	bool is_empty();
	bool enqueue(JobEventPtr e);
	JobEventPtr dequeue(void);

	friend std::ostream& operator<< (std::ostream& out, QueueJobBuffer& e);
};

typedef typename boost::shared_ptr<QueueJobBuffer> QueueJobBufferPtr;

#endif /* QUEUEJOBBUFFER_H_ */
