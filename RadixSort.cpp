﻿#include "RadixSort.h"
#include "Data.h"
#include "ICommon.h"

#define BITS 2

void CRadixSort::Run(CData *data)
{
	int i, m = data->Get(0), pos = 0;
	int *b = new int[data->GetSize()]();
	int buckets=1<<BITS;
	int mask=buckets-1;
	for (i = 0; i < data->GetSize(); i++)
		if (data->Get(i) > m)
			m = data->Get(i);

	while ((m>>(pos*BITS)) > 0) {
		if (ShouldHalt())
			return;

		int bucket[1<<BITS] = { 0 };
		for (i = 0; i < data->GetSize(); i++)
			bucket[(data->Get(i)>>(pos*BITS)) & mask]++;
			if(i%2==0)
			common->Delay(sleepTime);


		for (i = 1; i < buckets; i++)
			bucket[i] += bucket[i - 1];
			//Sleep(1);

		for (i = data->GetSize() - 1; i >= 0; i--)
			b[--bucket[(data->Get(i)>>(pos*BITS)) & mask]] = data->Get(i);


		for (i = 0; i < data->GetSize(); i++) {
			data->Set(i, b[i]);
			if(i%2==0)
			common->Delay(sleepTime);
		}
		
		pos++;
	}

	delete b;
}
