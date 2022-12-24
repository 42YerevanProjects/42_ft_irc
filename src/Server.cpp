/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 20:58:45 by shovsepy          #+#    #+#             */
/*   Updated: 2022/12/18 21:12:09 by shovsepy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* Constructor and Destructor */

Server::Server(const std::string &port, const std::string &pass) : _port(port), _pass(pass)
{
    _running = 1;
    _sock = create_socket();
    
    _host = "127.0.0.1";
}

Server::~Server() {}

/* Create Socket */

int     Server:create_socket()
{
    // oppening a socket

    int sock_fd = socket(AF_INET, SOCK_STREA, 0);
    if (sock_fd < 0)
        throw std::runtime_error("Error while opening a socket!");

    // forcefully attacing socket to the port by making it reusable

    int optval = 1;
    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)))
        throw std::runtime_error("Error while setting socket options!");

    // making the socket NON-BLOCKING

    if (fcntl(sock_fd, F_SETFL, O_NONBLOCK))
        throw std::runtime_error("Error while setting socket to NON-BLOCKING!");

    // gathering neccessary data for binding
    
    struct sockaddr_in  serv_addr = {};

    bzero((char*) &serv_addr, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(std::stoi(_port));

    // Bind socket to an IP address on selected port
    
    if (bind(sock_fd, (sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        throw std::runtime_error("Error while binding a socket!");

    // Listening for requests

    if (listen(sock_fd, MAX_CONNECTIONS) < 0)
        throw std::runtime_error("Error while listening on a socket!");

    return sock_fd;
}