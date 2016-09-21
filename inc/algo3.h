int maxCrossingSum(int * t, int *head, int med, int *tail) {
    int sum = 0, left_sum = INT_MIN, max_left = med;
    for (int i = med; i >= *head; --i) {
        sum += t[i];
        if (sum > left_sum) {
          left_sum = sum;
          max_left = i;
        }
    }
    sum = 0;
    int right_sum = INT_MIN, max_right = med;
    for (int i = med + 1; i <= *tail; ++i) {
        sum += t[i];
        if (sum > right_sum) {
          right_sum = sum;
          max_right = i;
        }
    }
    *head = max_left;
    *tail = max_right;
    return left_sum + right_sum;
}

int maxSubArraySum(int * t, int *head, int *tail) {
    if (*head == *tail)
        return t[*head];

    int med = (*head + *tail) / 2;
    //gauche
    int left_head = *head, left_tail = med;
    int left_sum = maxSubArraySum(t, &left_head, &left_tail);
    //droite
    int right_head = med + 1, right_tail = *tail;
    int right_sum = maxSubArraySum(t, &right_head, &right_tail);
    //milleu
    int cross_head = *head, cross_tail = *tail;
    int cross_sum = maxCrossingSum(t, &cross_head, med, &cross_tail);

    if(left_sum >= right_sum && left_sum >= cross_sum) {
        *head = left_head;
        *tail = left_tail;
        return left_sum;
    } else if (right_sum >= left_sum && right_sum >= cross_sum) {
        *head = right_head;
        *tail = right_tail;
        return right_sum;
    } else {
        *head = cross_head;
        *tail = cross_tail;
        return cross_sum;
    }
}

int algo3 (int * t, int n, int *start_max, int *end_max) {
    *start_max = 0;
    *end_max = n - 1;
    return maxSubArraySum(t, start_max, end_max);
}
