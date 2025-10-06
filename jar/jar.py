class Jar:

    # Constructor method, set default capacity to 12
    def __init__(self, capacity=12):

        self._capacity = capacity
        self._size = 0

    # Define output when print str is called
    def __str__(self):

        return "🍪" * self._size

    # Define deposit method
    def deposit(self, n):
        self._size += n

    def withdraw(self, n):
        self._size -= n

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size


def main():

    jar = Jar(5)

    print(str(jar.capacity))

    print(str(jar))

    jar.deposit(4)
    print(str(jar))
    print(str(jar.size))

    jar.withdraw(3)
    print(str(jar))
    print(str(jar.size))

main()
