from xor_cypher import crypt_old, crypt

# Menu representation
def print_menu():
    print(25 * "-", "CYPHER MENU", 2 * "-")
    print("1. Encrypt file fast")
    print("2. Encrypt file with random byte stuffing")
    print("3. Decrypt file fast")
    print("4. DEV Encrypt file old ( benchmark purpose )")
    print("5. DEV Decrypt file old ( benchmark purpose )")
    print("6. Exit")
    print(73 * "-")


# Menu logic
def menu():
    loop = True

    while loop:
        print_menu()
        choice = input("Enter your choice [1-6]: ")

        if choice == '1':  # NUMPY, NO BYTE STUFFING - ENCRYPTION

            origin = input(
                "Enter the file you want to encrypt (e.g.: name.jpg ( same dir )  or the filepath of the file): ")
            enc = input(
                "Enter a second file you want use to encrypt the first one (e.g.: name.pdf ( same dir )  or the filepath of the file): ")
            crypt(False, origin, enc, origin + ".key")
            print("Finished\n\n\n")

        elif choice == '2':  # NUMPY, BYTE STUFFING - ENCRYPTION

            origin = input(
                "Enter the file you want to encrypt (e.g.: name.jpg ( same dir )  or the filepath of the file): ")
            enc = input(
                "Enter a second file you want use to encrypt the first one (e.g.: name.pdf ( same dir )  or the filepath of the file): ")
            crypt(True, origin, enc, origin + ".key")
            print("Finished\n\n\n")

        elif choice == '3':  # NUMPY, NO STUFFING - DECRYPTION

            origin = input(
                "Enter the file you want to decrypt (e.g.: name.jpg.key ( same dir )  or the filepath of the file): ")
            enc = input(
                "Enter the second file you used to encrypt the first one (e.g.: name.pdf ( same dir )  or the filepath of the file): ")
            crypt(False, origin, enc, origin[:-4])
            print("Finished\n\n\n")

        elif choice == '4':  # NO NUMPY, STUFFING - ENCRYPTION

            origin = input(
                "Enter the file you want to encrypt (e.g.: name.jpg ( same dir )  or the filepath of the file): ")
            enc = input(
                "Enter a second file you want use to encrypt the first one (e.g.: name.pdf ( same dir )  or the filepath of the file): ")
            crypt_old(origin, enc, origin + ".key")
            print("Finished\n\n\n")

        elif choice == '5':  # NO NUMPY, STUFFING - DECRYPTION

            origin = input(
                "Enter the file you want to decrypt (e.g.: name.jpg.key ( same dir )  or the filepath of the file): ")
            enc = input(
                "Enter the second file you used to encrypt the first one (e.g.: name.pdf ( same dir )  or the filepath of the file): ")
            crypt_old(origin, enc, origin[:-4])
            print("Finished\n\n\n")

        elif choice == '6':  # EXIT
            return
        else:
            # Any inputs other than values 1-4 we print an error message
            input("Wrong menu selection. Enter any key to try again..")
    return

if __name__ == '__main__':
    menu()