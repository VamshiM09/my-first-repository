
def bubble_sort(arr):
    n = len(arr)
    for i in range(n - 1):  # Outer loop
        for j in range(n - i - 1):  # Inner loop
            if arr[j] > arr[j + 1]:  # Swap if greater
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr
