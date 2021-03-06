﻿#include "InsertionSort.h"
#include "Data.h"
#include "ICommon.h"

void CInsertionSort::Run(CData *data)
{
	for (int i = 0; i < data->GetSize(); i++) {
		int j = i;
		while (j > 0 && data->Get(j) < data->Get(j - 1)) {
			if (ShouldHalt())
				return;

			data->Swap(j, j - 1);
			j--;

			common->Delay(sleepTime);
		}
	}
}
