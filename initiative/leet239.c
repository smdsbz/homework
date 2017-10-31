/*
  LeetCode #239 - Sliding Window Maximum
  (https://leetcode.com/problems/sliding-window-maximum/)

  solution of O(n) below beat only 10% of submissions
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const char *__author__ = "smdsbz@GitHub.com";



void
printList(int *nums, int numsSize) {
  /*  DEBUG: prints out the list */
  size_t i;
  for (i = 0; i < numsSize; i++) {
    printf("%4d", nums[i]);
  }
  putchar('\n');
}




int *
maxSlidingWindow(int *nums, int numsSize, int k, int *returnSize) {
  /**** Magic here ****
    1. set `left`, `right` verges
    2. find max and set `max_in_curr_win`, `max_offset_from_left`
        meanwhile: set elements left of `max_in_curr_win` to `max_in_curr_win`
        HACK: (performance) only set element `left` to `max_in_curr_win`
    3. move window:
        `left`++
        `right`++
        `max_offset_from_left`-- till touches 0
        go back to 2 till done
  */

  // input validity checking
  if (numsSize == 0) {
    // should they give `[]` as `nums`?!
    *returnSize = 0;
    return NULL;
  }

  // set `returnSize`
  *returnSize = numsSize - k + 1;

  // bakup `nums`
  int *nums_bak = nums; // LeetCode style NFS:
                        //  you magic on the input

  // init vars
  int left  = 1,      // skip the first window, specially treated
      max_offset = 0, // general offset respective to `nums`
                      // save me the time for `max_offset_from_left--`
      right	= k,
      i;

  // treat first window
  for (i = 1; i < k; i++) {
    if (nums[max_offset] < nums[i]) { max_offset = i; }
  }
  nums_bak[0] = nums[max_offset];
  if (max_offset < left) {
    for (i = left, max_offset = left; i <= right; i++) {
      if (nums[max_offset] < nums[i]) { max_offset = i; }
    }
  }

  // iter over the rest
  while (right < numsSize) {

    // set `max_offset`
    if (nums_bak[max_offset] < nums_bak[right]) { max_offset = right; }

    // set `nums[left]` to `max_in_curr_win`
    nums_bak[left] = nums[max_offset];

    // move window
    left++; right++;
    if (max_offset < left) {
      for (i = left, max_offset = left; i <= right; i++) {
        if (nums[max_offset] < nums[i]) { max_offset = i; }
      }
    }

    // DEBUG: print out
    // printList(nums_bak, numsSize);
  }

  // return
  return nums_bak;  // LeetCode style NFS
}



int main(int argc, const char **argv) {

  // int nums[8] = {1, 3, -1, -3, 5, 3, 6, 7};
  // int k = 3;

  // int nums[0] = {};
  // int k = 0;

  // int nums[6] = {1, 3, 1, 2, 0, 5};
  // int k = 3;

  int nums[2] = {1, -1};
  int k = 1;

  int returnSize;
  int *maxes = maxSlidingWindow(nums, 2, k, &returnSize);

  printList(maxes, returnSize);

  return 0;
}
