class Jar:
    def __init__(self, capacity=12):
        ...

    def __str__(self):


        return 🍪

    def deposit(self, n):
        ...

    def withdraw(self, n):
        ...

    @property
    def capacity(self):
        ...

    @property
    def size(self):
        ...


def main():

    jar = Jar()

    print(str(jar.capacity))

    print(str(jar))

    jar.deposit(2)
    print(str(jar))

    jar.withdraw(1)
    print(str(jar))
    



main()
