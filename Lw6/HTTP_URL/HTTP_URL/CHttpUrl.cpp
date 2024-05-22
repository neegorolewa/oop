#include "CHttpUrl.h"

const std::map<Protocol, std::string> PROTOCOL_TO_STRING
{
	{ Protocol::HTTP, "http"},
	{ Protocol::HTTPS, "https"}
};

const std::map<std::string, Protocol> STRING_TO_PROTOCOL
{
	{"http", Protocol::HTTP},
	{"https", Protocol::HTTPS}
};

const std::map<Protocol, unsigned short> PORT_OF_PROTOCOL
{
	{Protocol::HTTP, 80},
	{Protocol::HTTPS, 443}
};

const unsigned short MAX_PORT_VALUE = 65535;
const unsigned short MIN_PORT_VALUE = 1;

const std::string PROTOCOL_REGEX_STR = "(https?)://";
const std::string DOMAIN_REGEX_STR = "([\\w-.,]+)";
const std::string PORT_REGEX_STR = "(?:\\:(\\d{1,5}))?";
const std::string DOCUMENT_REGEX_STR = "(\\S*)";

const std::regex URL_REGEX = std::regex("^" + PROTOCOL_REGEX_STR + DOMAIN_REGEX_STR + PORT_REGEX_STR + "(?:/" + DOCUMENT_REGEX_STR + ")?" + "$", std::regex_constants::icase);
const std::regex DOMAIN_REGEX = std::regex("^" + DOMAIN_REGEX_STR + "$");
const std::regex DOCUMENT_REGEX = std::regex("^" + DOCUMENT_REGEX_STR + "$");

const std::string INVALID_URL = "Invalid url";
const std::string INVALID_PROTOCOL = "Invalid protocol. Protocol must be 'http' or 'https'";
const std::string INVALID_PORT = "Invalid port. Port must be between 1 and 65535";
const std::string INVALID_DOMAIN = "Invalid domain";
const std::string INVALID_DOCUMENT = "Invalid document";

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::cmatch result;
	if (!std::regex_match(url.c_str(), result, URL_REGEX))
	{
		throw CUrlParsingError(INVALID_URL);
	}

	m_protocol = GetProtocolOfString(result[1]);

	m_domain = result[2];

	m_port = ParsePort(result[3]);

	m_document = "/";
	m_document += result[4];
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
	: CHttpUrl(domain, document, protocol, PORT_OF_PROTOCOL.at(protocol))
{
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
	: m_protocol{ protocol }
{
	if (!IsValidDomain(domain))
	{
		throw std::invalid_argument(INVALID_DOMAIN);
	}

	m_domain = domain;

	if (!IsValidDocument(document))
	{
		throw std::invalid_argument(INVALID_DOCUMENT);
	}

	if (document[0] != '/')
	{
		m_document = "/" + document;
	}
	else
	{
		m_document = document;
	}

	if (port < MIN_PORT_VALUE || port > MAX_PORT_VALUE)
	{
		throw std::invalid_argument(INVALID_PORT);
	}
	m_port = port;
}

std::string CHttpUrl::GetURL() const
{
	std::string port;
	if (m_port == PORT_OF_PROTOCOL.at(m_protocol))
	{
		port = "";
	}
	else
	{
		port = ":" + std::to_string(m_port);
	}

	return PROTOCOL_TO_STRING.at(m_protocol) + "://" + m_domain + port + m_document;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

Protocol CHttpUrl::GetProtocolOfString(const std::string& str)
{
	std::string protocolStr = str;
	std::transform(protocolStr.begin(), protocolStr.end(), protocolStr.begin(), [](unsigned char ch)
		{
			return std::tolower(ch);
		}
	);

	if (STRING_TO_PROTOCOL.find(protocolStr) != STRING_TO_PROTOCOL.end())
	{
		return STRING_TO_PROTOCOL.at(protocolStr);
	}

	throw CUrlParsingError(INVALID_PROTOCOL);
}

unsigned short CHttpUrl::ParsePort(const std::string& str)
{
	if (str.empty())
	{
		return PORT_OF_PROTOCOL.at(m_protocol);
	}

	int portInt;
	try
	{
		portInt = std::stoi(str);
	}
	catch (...)
	{
		throw CUrlParsingError(INVALID_PORT);
	}

	if (portInt < MIN_PORT_VALUE || portInt > MAX_PORT_VALUE)
	{
		throw CUrlParsingError(INVALID_PORT);
	}

	return portInt;
}

bool CHttpUrl::IsValidDomain(const std::string& domain)
{
	std::cmatch res;
	return(std::regex_match(domain.c_str(), res, DOMAIN_REGEX));
}

bool CHttpUrl::IsValidDocument(const std::string& document)
{
	std::cmatch res;
	return(std::regex_match(document.c_str(), res, DOCUMENT_REGEX) || document.empty());
}

std::string ProtocolToStr(const Protocol& protocol)
{
	return PROTOCOL_TO_STRING.at(protocol);
}
