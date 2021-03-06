﻿#include "BubbleSort.h"
#include "Data.h"
#include "ICommon.h"

void CBubbleSort::Run(CData *data)
{
	for (int i = 0; i < data->GetSize() - 1; i++) {
		for (int j = 0; j < data->GetSize() - i - 1; j++) {
			if (ShouldHalt())
				return;
			int p = data->Get(j);
			int q = data->Get(j+1);
			if (p > q) {
				data->Set(j, q);
				data->Set(j+1, p);
			}
			common->Delay(sleepTime);
		}
	}
}
