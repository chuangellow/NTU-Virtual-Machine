import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('localhost', 1126)
server_socket.bind(server_address)

server_socket.listen(1)

print('waiting for a connection')
connection, client_address = server_socket.accept()
try:
    print('connection from', client_address)
    message = 'R11944040 sending from the server'
    with open('/r11944040_servervol/sent.txt', 'w') as f:
        f.write(message)
    connection.sendall(message.encode('utf-8'))
finally:
    connection.close()
    server_socket.close()
