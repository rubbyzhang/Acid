#pragma once

#include "Engine/Exports.hpp"
#include "Network/Tcp/TcpSocket.hpp"
#include "Network/IpAddress.hpp"
#include "FtpDataChannel.hpp"
#include "FtpResponse.hpp"
#include "FtpResponseDirectory.hpp"
#include "FtpResponseListing.hpp"

namespace acid
{
	///
	/// \brief A FTP client
	///
	class ACID_EXPORT Ftp
	{
	private:
		TcpSocket m_commandSocket; /// Socket holding the control connection with the server.
		std::string m_receiveBuffer; /// Received command data that is yet to be processed.
	public:
		///
		/// \brief Destructor
		///
		/// Automatically closes the connection with the server if
		/// it is still opened.
		///
		~Ftp();

		///
		/// \brief Connect to the specified FTP server
		///
		/// The port has a default value of 21, which is the standard
		/// port used by the FTP protocol. You shouldn't use a different
		/// value, unless you really know what you do.
		/// This function tries to connect to the server so it may take
		/// a while to complete, especially if the server is not
		/// reachable. To avoid blocking your application for too long,
		/// you can use a timeout. The default value, Time::Zero, means that the
		/// system timeout will be used (which is usually pretty long).
		///
		/// \param server  Name or address of the FTP server to connect to
		/// \param port    Port used for the connection
		/// \param timeout Maximum time to wait
		///
		/// \return Server response to the request
		///
		/// \see disconnect
		///
		FtpResponse Connect(const IpAddress &server, unsigned short port = 21, Time timeout = Time::ZERO);

		///
		/// \brief Close the connection with the server
		///
		/// \return Server response to the request
		///
		/// \see connect
		///
		FtpResponse Disconnect();

		///
		/// \brief Log in using an anonymous account
		///
		/// Logging in is mandatory after connecting to the server.
		/// Users that are not logged in cannot perform any operation.
		///
		/// \return Server response to the request
		///
		FtpResponse Login();

		///
		/// \brief Log in using a username and a password
		///
		/// Logging in is mandatory after connecting to the server.
		/// Users that are not logged in cannot perform any operation.
		///
		/// \param name     User name
		/// \param password Password
		///
		/// \return Server response to the request
		///
		FtpResponse Login(const std::string &name, const std::string &password);

		///
		/// \brief Send a null command to keep the connection alive
		///
		/// This command is useful because the server may close the
		/// connection automatically if no command is sent.
		///
		/// \return Server response to the request
		///
		FtpResponse KeepAlive();

		///
		/// \brief Get the current working directory
		///
		/// The working directory is the root path for subsequent
		/// operations involving directories and/or filenames.
		///
		/// \return Server response to the request
		///
		/// \see getDirectoryListing, changeDirectory, parentDirectory
		///
		FtpResponseDirectory GetWorkingDirectory();

		///
		/// \brief Get the contents of the given directory
		///
		/// This function retrieves the sub-directories and files
		/// contained in the given directory. It is not recursive.
		/// The \a directory parameter is relative to the current
		/// working directory.
		///
		/// \param directory Directory to list
		///
		/// \return Server response to the request
		///
		/// \see getWorkingDirectory, changeDirectory, parentDirectory
		///
		FtpResponseListing GetDirectoryListing(const std::string &directory = "");

		///
		/// \brief Change the current working directory
		///
		/// The new directory must be relative to the current one.
		///
		/// \param directory New working directory
		///
		/// \return Server response to the request
		///
		/// \see getWorkingDirectory, getDirectoryListing, parentDirectory
		///
		FtpResponse ChangeDirectory(const std::string &directory);

		///
		/// \brief Go to the parent directory of the current one
		///
		/// \return Server response to the request
		///
		/// \see getWorkingDirectory, getDirectoryListing, changeDirectory
		///
		FtpResponse ParentDirectory();

		///
		/// \brief Create a new directory
		///
		/// The new directory is created as a child of the current
		/// working directory.
		///
		/// \param name Name of the directory to create
		///
		/// \return Server response to the request
		///
		/// \see deleteDirectory
		///
		FtpResponse createDirectory(const std::string &name); // TODO

		///
		/// \brief Remove an existing directory
		///
		/// The directory to remove must be relative to the
		/// current working directory.
		/// Use this function with caution, the directory will
		/// be removed permanently!
		///
		/// \param name Name of the directory to remove
		///
		/// \return Server response to the request
		///
		/// \see createDirectory
		///
		FtpResponse deleteDirectory(const std::string &name); // TODO

		///
		/// \brief Rename an existing file
		///
		/// The filenames must be relative to the current working
		/// directory.
		///
		/// \param file    File to rename
		/// \param newName New name of the file
		///
		/// \return Server response to the request
		///
		/// \see deleteFile
		///
		FtpResponse RenameFile(const std::string &file, const std::string &newName);

		///
		/// \brief Remove an existing file
		///
		/// The file name must be relative to the current working
		/// directory.
		/// Use this function with caution, the file will be
		/// removed permanently!
		///
		/// \param name File to remove
		///
		/// \return Server response to the request
		///
		/// \see renameFile
		///
		FtpResponse deleteFile(const std::string &name); // TODO

		///
		/// \brief Download a file from the server
		///
		/// The filename of the distant file is relative to the
		/// current working directory of the server, and the local
		/// destination path is relative to the current directory
		/// of your application.
		/// If a file with the same filename as the distant file
		/// already exists in the local destination path, it will
		/// be overwritten.
		///
		/// \param remoteFile Filename of the distant file to download
		/// \param localPath  The directory in which to put the file on the local computer
		/// \param mode       Transfer mode
		///
		/// \return Server response to the request
		///
		/// \see upload
		///
		FtpResponse Download(const std::string &remoteFile, const std::string &localPath, FtpTransferMode mode = FTP_MODE_BINARY);

		///
		/// \brief Upload a file to the server
		///
		/// The name of the local file is relative to the current
		/// working directory of your application, and the
		/// remote path is relative to the current directory of the
		/// FTP server.
		///
		/// The append parameter controls whether the remote file is
		/// appended to or overwritten if it already exists.
		///
		/// \param localFile  Path of the local file to upload
		/// \param remotePath The directory in which to put the file on the server
		/// \param mode       Transfer mode
		/// \param append     Pass true to append to or false to overwrite the remote file if it already exists
		///
		/// \return Server response to the request
		///
		/// \see download
		///
		FtpResponse Upload(const std::string &localFile, const std::string &remotePath, FtpTransferMode mode = FTP_MODE_BINARY, bool append = false);

		///
		/// \brief Send a command to the FTP server
		///
		/// While the most often used commands are provided as member
		/// functions in the Ftp class, this method can be used
		/// to send any FTP command to the server. If the command
		/// requires one or more parameters, they can be specified
		/// in \a parameter. If the server returns information, you
		/// can extract it from the response using Response::GetFullMessage().
		///
		/// \param command   Command to send
		/// \param parameter Command parameter
		///
		/// \return Server response to the request
		///
		FtpResponse SendCommand(const std::string &command, const std::string &parameter = "");
	private:
		///
		/// \brief Receive a response from the server
		///
		/// This function must be called after each call to
		/// sendCommand that expects a response.
		///
		/// \return Server response to the request
		///
		FtpResponse GetResponse();
	};
}
