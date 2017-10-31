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

  // set `returnSize`
  *returnSize = numsSize - k + 1;
  if (numsSize == 0) { *returnSize = 0; } // should they give `[]` as `nums`?!

  // bakup `nums`
  int *nums_bak = nums; // LeetCode style NFS:
                        //  you magic on the input

  // init vars
  int *maxes = (int *)malloc(*returnSize * sizeof(int));
  if (maxes == NULL) { return NULL; }
  int left  = 0,
      max_offset = 0, // general offset respective to `nums`
                      // save me the time for `max_offset_from_left--`
      right	= k - 1,
      i, j;

  // validity checking
  if (k == 0) {
    return maxes;
  }

  // iter over
  while (right < numsSize) {

    // set `max_in_curr_win`, `max_offset_from_left`
    for (i = max_offset + 1; i <= right; i++) {
      // NOTE: for-loop starts from `max_offset+1`, still O(n)
      if (nums[max_offset] < nums[i]) {
        max_offset = i;
      }
    }

    // set `nums[left]` to `max_in_curr_win`
    nums_bak[left] = nums[max_offset];

    // move window
    left++; right++;
    if (max_offset < left) {
      max_offset = left;
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

  int nums[3] = {7, 2, 4};
  int k = 2;

  int *returnSize = (int *)malloc(1 * sizeof(int));
  int *maxes = maxSlidingWindow(nums, 3, k, returnSize);

  printList(maxes, *returnSize);

  return 0;
}
