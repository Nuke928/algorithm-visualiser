﻿#include "QuickSort.h"
#include "Data.h"
#include "ICommon.h"

void CQuickSort::Run(CData *data)
{
	Sort(data, 0, data->GetSize() - 1);
}

void CQuickSort::Sort(CData *data, int begin, int end)
{
	if (end > begin) {
		int pivot = data->Get((begin + end) / 2);
		int left = begin;
		int right = end;

		data->Swap(begin, (begin + end) / 2);
		pivot = data->Get(begin);

		while (left < right) {
			if (ShouldHalt())
				return;

			if (data->Get(left) <= pivot) {
				left++;
			} else {
				while (left < --right && data->Get(right) >= pivot);
				data->Swap(left, right);
			}

			common->Delay(sleepTime);
		}

		left--;
		data->Swap(begin, left);
		Sort(data, begin, left);
		Sort(data, right, end);
	}
}
