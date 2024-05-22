#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../HTTP_URL/CHttpUrl.h"

TEST_CASE("Create CHttpUrl(url)")
{
	WHEN("full url http")
	{
		CHttpUrl url("http://domain:9000/some-document");
		THEN("Right fields")
		{
			REQUIRE(url.GetURL() == "http://domain:9000/some-document");
			REQUIRE(ProtocolToStr(url.GetProtocol()) == "http");
			REQUIRE(url.GetDomain() == "domain");
			REQUIRE(url.GetPort() == 9000);
			REQUIRE(url.GetDocument() == "/some-document");
		}
	}

	WHEN("full url https")
	{
		CHttpUrl url("https://domain:9000/some-document");
		THEN("Right fields")
		{
			REQUIRE(url.GetURL() == "https://domain:9000/some-document");
			REQUIRE(ProtocolToStr(url.GetProtocol()) == "https");
			REQUIRE(url.GetDomain() == "domain");
			REQUIRE(url.GetPort() == 9000);
			REQUIRE(url.GetDocument() == "/some-document");
		}
	}

	WHEN("full url HTTP")
	{
		CHttpUrl url("HTTP://domain:9000/some-document");
		THEN("Right fields")
		{
			REQUIRE(url.GetURL() == "http://domain:9000/some-document");
			REQUIRE(ProtocolToStr(url.GetProtocol()) == "http");
			REQUIRE(url.GetDomain() == "domain");
			REQUIRE(url.GetPort() == 9000);
			REQUIRE(url.GetDocument() == "/some-document");
		}
	}

	WHEN("full url HTTPS")
	{
		CHttpUrl url("HTTPS://domain:9000/some-document");
		THEN("Right fields")
		{
			REQUIRE(url.GetURL() == "https://domain:9000/some-document");
			REQUIRE(ProtocolToStr(url.GetProtocol()) == "https");
			REQUIRE(url.GetDomain() == "domain");
			REQUIRE(url.GetPort() == 9000);
			REQUIRE(url.GetDocument() == "/some-document");
		}
	}

	WHEN("url without document")
	{
		CHttpUrl url("http://domain:9000");
		THEN("Right fields, document = /")
		{
			REQUIRE(url.GetURL() == "http://domain:9000/");
			REQUIRE(ProtocolToStr(url.GetProtocol()) == "http");
			REQUIRE(url.GetDomain() == "domain");
			REQUIRE(url.GetPort() == 9000);
			REQUIRE(url.GetDocument() == "/");
		}
	}

	WHEN("url without port")
	{
		CHttpUrl url("https://domain/some-document");
		THEN("Right fields, default port for https protocol = 443")
		{
			REQUIRE(url.GetURL() == "https://domain/some-document");
			REQUIRE(ProtocolToStr(url.GetProtocol()) == "https");
			REQUIRE(url.GetDomain() == "domain");
			REQUIRE(url.GetPort() == 443);
			REQUIRE(url.GetDocument() == "/some-document");
		}
	}

	WHEN("url with default port (80)")
	{
		CHttpUrl url("http://domain:80/some-document");
		THEN("Right fields, port not print")
		{
			REQUIRE(url.GetURL() == "http://domain/some-document");
			REQUIRE(ProtocolToStr(url.GetProtocol()) == "http");
			REQUIRE(url.GetDomain() == "domain");
			REQUIRE(url.GetPort() == 80);
			REQUIRE(url.GetDocument() == "/some-document");
		}
	}

	WHEN("url not valid")
	{
		THEN("exception")
		{
			REQUIRE_THROWS_AS(CHttpUrl("not valid url"), CUrlParsingError);
		}
	}

	WHEN("protocol is not valid")
	{
		THEN("catch exception")
		{
			REQUIRE_THROWS_AS(CHttpUrl("htap://domain:80/some-document"), CUrlParsingError);
		}
	}

	WHEN("domain is not valid")
	{
		THEN("catch exception")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://do()main:80/some-document"), CUrlParsingError);
		}
	}

	WHEN("port out of range")
	{
		THEN("catch exception")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://domain:8000000/some-document"), CUrlParsingError);
		}
	}

	WHEN("Document is not valid")
	{
		THEN("catch exception")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://domain:80/some document"), CUrlParsingError);
		}
	}
}

TEST_CASE("Create CHttpUrl(domain, document, protocol)")
{
	WHEN("http protocol")
	{
		CHttpUrl url("domain", "/some-doc", Protocol::HTTP);
		THEN("right url and port = 80")
		{
			REQUIRE(url.GetURL() == "http://domain/some-doc");
			REQUIRE(url.GetPort() == 80);
		}
	}

	WHEN("https protocol")
	{
		CHttpUrl url("domain", "/some-doc", Protocol::HTTPS);
		THEN("right url and port = 443")
		{
			REQUIRE(url.GetURL() == "https://domain/some-doc");
			REQUIRE(url.GetPort() == 443);
		}
	}
}

TEST_CASE("Create CHttpUrl(domain, document, protocol, port)")
{
	WHEN("get all members url")
	{
		CHttpUrl url("domain", "/some-doc", Protocol::HTTP, 9000);
		THEN("create right url")
		{
			REQUIRE(url.GetURL() == "http://domain:9000/some-doc");
			REQUIRE(ProtocolToStr(url.GetProtocol()) == "http");
			REQUIRE(url.GetDomain() == "domain");
			REQUIRE(url.GetPort() == 9000);
			REQUIRE(url.GetDocument() == "/some-doc");
		}
	}

	WHEN("document without /")
	{
		CHttpUrl url("domain", "some-doc", Protocol::HTTP, 9000);
		THEN("add / for document")
		{
			REQUIRE(url.GetURL() == "http://domain:9000/some-doc");
			REQUIRE(ProtocolToStr(url.GetProtocol()) == "http");
			REQUIRE(url.GetDomain() == "domain");
			REQUIRE(url.GetPort() == 9000);
			REQUIRE(url.GetDocument() == "/some-doc");
		}
	}

	WHEN("document is empty")
	{
		CHttpUrl url("domain", "", Protocol::HTTP, 9000);
		THEN("crate empty document with /")
		{
			REQUIRE(url.GetURL() == "http://domain:9000/");
			REQUIRE(ProtocolToStr(url.GetProtocol()) == "http");
			REQUIRE(url.GetDomain() == "domain");
			REQUIRE(url.GetPort() == 9000);
			REQUIRE(url.GetDocument() == "/");
		}
	}

	WHEN("create with default port")
	{
		CHttpUrl url("domain", "/some-doc", Protocol::HTTPS, 443);
		THEN("all be right")
		{
			REQUIRE(url.GetURL() == "https://domain/some-doc");
			REQUIRE(ProtocolToStr(url.GetProtocol()) == "https");
			REQUIRE(url.GetDomain() == "domain");
			REQUIRE(url.GetPort() == 443);
			REQUIRE(url.GetDocument() == "/some-doc");
		}
	}
}