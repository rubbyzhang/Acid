#pragma once

#include <string>
#include "Engine/Exports.hpp"

namespace acid
{
	///
	/// \brief Status codes possibly returned by a FTP response
	///
	enum FtpResponseStatus
	{
		// 1xx: the requested action is being initiated, expect another reply before proceeding with a new command.
		FTP_RESPONCE_RESTART_MARKER_REPLY = 110, /// Restart marker reply.
		FTP_RESPONCE_SERVICE_READY_SOON = 120, /// Service ready in N minutes.
		FTP_RESPONCE_DATA_CONNECTION_ALREADY_OPENED = 125, /// Data connection already opened, transfer starting.
		FTP_RESPONCE_OPENING_DATA_CONNECTION = 150, /// File status ok, about to open data connection.

		// 2xx: the requested action has been successfully completed.
		FTP_RESPONCE_OK = 200, /// Command ok.
		FTP_RESPONCE_POINTLESS_COMMAND = 202, /// Command not implemented.
		FTP_RESPONCE_SYSTEM_STATUS = 211, /// System status, or system help reply.
		FTP_RESPONCE_DIRECTORY_STATUS = 212, /// Directory status.
		FTP_RESPONCE_FILE_STATUS = 213, /// File status.
		FTP_RESPONCE_HELP_MESSAGE = 214, /// Help message.
		FTP_RESPONCE_SYSTEM_TYPE = 215, /// NAME system type, where NAME is an official system name from the list in the Assigned Numbers document.
		FTP_RESPONCE_SERVICE_READY = 220, /// Service ready for new user.
		FTP_RESPONCE_CLOSING_CONNECTION = 221, /// Service closing control connection.
		FTP_RESPONCE_DATA_CONNECTION_OPENED = 225, /// Data connection open, no transfer in progress.
		FTP_RESPONCE_CLOSING_DATA_CONNECTION = 226, /// Closing data connection, requested file action successful.
		FTP_RESPONCE_ENTERING_PASSIVE_MODE = 227, /// Entering passive mode.
		FTP_RESPONCE_LOGGEDIN = 230, /// User logged in, proceed. Logged out if appropriate.
		FTP_RESPONCE_FILEACTION_OK = 250, /// Requested file action ok.
		FTP_RESPONCE_DIRECTORY_OK = 257, /// PATHNAME created.

		// 3xx: the command has been accepted, but the requested action is dormant, pending receipt of further information.
		FTP_RESPONCE_NEED_PASSWORD = 331, /// User name ok, need password.
		FTP_RESPONCE_NEED_ACCOUNT_TO_LOGIN = 332, /// Need account for login.
		FTP_RESPONCE_NEED_INFORMATION = 350, /// Requested file action pending further information.

		// 4xx: the command was not accepted and the requested action did not take place, but the error condition is temporary and the action may be requested again.
		FTP_RESPONCE_SERVICE_UNAVAILABLE = 421, /// Service not available, closing control connection.
		FTP_RESPONCE_DATA_CONNECTION_UNAVAILABLE = 425, /// Can't open data connection.
		FTP_RESPONCE_TRANSFER_ABORTED = 426, /// Connection closed, transfer aborted.
		FTP_RESPONCE_FILE_ACTION_ABORTED = 450, /// Requested file action not taken.
		FTP_RESPONCE_LOCAL_ERROR = 451, /// Requested action aborted, local error in processing.
		FTP_RESPONCE_INSUFFICIENT_STORAGE_SPACE = 452, /// Requested action not taken; insufficient storage space in system, file unavailable.

		// 5xx: the command was not accepted and the requested action did not take place.
		FTP_RESPONCE_COMMAND_UNKNOWN = 500, /// Syntax error, command unrecognized.
		FTP_RESPONCE_PARAMETERS_UNKNOWN = 501, /// Syntax error in parameters or arguments.
		FTP_RESPONCE_COMMAND_NOT_IMPLEMENTED = 502, /// Command not implemented.
		FTP_RESPONCE_BAD_COMMAND_SEQUENCE = 503, /// Bad sequence of commands.
		FTP_RESPONCE_PARAMETER_NOT_IMPLEMENTED = 504, /// Command not implemented for that parameter.
		FTP_RESPONCE_NOT_LOGGEDIN = 530, /// Not logged in.
		FTP_RESPONCE_NEED_ACCOUNT_TO_STORE = 532, /// Need account for storing files.
		FTP_RESPONCE_FILE_UNAVAILABLE = 550, /// Requested action not taken, file unavailable.
		FTP_RESPONCE_PAGE_TYPE_UNKNOWN = 551, /// Requested action aborted, page type unknown.
		FTP_RESPONCE_NOT_ENOUGH_MEMORY = 552, /// Requested file action aborted, exceeded storage allocation.
		FTP_RESPONCE_FILENAME_NOT_ALLOWED = 553, /// Requested action not taken, file name not allowed.

		// 10xx: custom codes.
		FTP_RESPONCE_INVALID_RESPONSE = 1000, /// Not part of the FTP standard, generated by SFML when a received response cannot be parsed.
		FTP_RESPONCE_CONNECTION_FAILED = 1001, /// Not part of the FTP standard, generated by SFML when the low-level socket connection with the server fails.
		FTP_RESPONCE_CONNECTION_CLOSED = 1002, /// Not part of the FTP standard, generated by SFML when the low-level socket connection is unexpectedly closed.
		FTP_RESPONCE_INVALID_FILE = 1003  /// Not part of the FTP standard, generated by SFML when a local file cannot be read or written.
	};

	///
	/// \brief Define a FTP response.
	///
	class ACID_EXPORT FtpResponse
	{
	private:
		FtpResponseStatus m_status; /// Status code returned from the server.
		std::string m_message; /// Last message received from the server.
	public:
		///
		/// \brief Default constructor
		///
		/// This constructor is used by the FTP client to build
		/// the response.
		///
		/// \param code    Response status code
		/// \param message Response message
		///
		explicit FtpResponse(FtpResponseStatus code = FTP_RESPONCE_INVALID_RESPONSE, const std::string &message = "");

		///
		/// \brief Check if the status code means a success
		///
		/// This function is defined for convenience, it is
		/// equivalent to testing if the status code is < 400.
		///
		/// \return True if the status is a success, false if it is a failure
		///
		bool IsOk() const;

		///
		/// \brief Get the status code of the response
		///
		/// \return Status code
		///
		FtpResponseStatus GetStatus() const;

		///
		/// \brief Get the full message contained in the response
		///
		/// \return The response message
		///
		const std::string &GetFullMessage() const;
	};
}
