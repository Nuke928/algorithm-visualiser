﻿#pragma once

#include <mutex>
#include <thread>
#include <vector>

static const int interval = 750;

/* Acts as encapsulation for sort algorithms, allowing us to catch all read and write calls */
class CData
{
public:
			CData(int size, int max);
			~CData();

	int		Get(int pos);
	void		Set(int pos, int value);

	bool		IsDirty(int pos) const { return pos == dirty; }

	std::mutex &	GetMutex() { return mutex; }
	int *		GetRawData() const { return data; }
	int *		GetTimeData() const { return timeData; }
	int		GetSize() const { return size; }
	int		GetMax() const { return max; }
	int		GetAccessCount() const { return accessCount; }
	int		GetWriteCount() const { return writeCount; }
	void		Swap(int i, int j);
	void		Randomize();

	void		Reset();

	void		ChangeSize(int newSize);

	void		Update(float dtTime);

private:
	int *		data;
	int *		timeData;
	int		dirty;
	int		max;
	int		size;
	std::mutex	mutex;

	int		accessCount;
	int		writeCount;

	std::vector<std::thread *> beepThreads;
};
