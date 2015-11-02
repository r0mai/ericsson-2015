#ifndef STREAM_HPP
#define STREAM_HPP

#include <iosfwd>
#include <string>
#include <sstream>
#include <array>
#include <memory>
#include <vector>
#include <climits>

template<typename Proto>
bool readProtoFromStream(Proto& proto, std::istream& stream);

template<typename Proto>
bool writeProtoOnStream(const Proto& proto, std::ostream& stream);


typedef std::array<unsigned char, 4> ProtoSize;

template<class T>
ProtoSize encodeSize(T size) {
	// instead of htonl:
	ProtoSize sizeBytes = { { static_cast<unsigned char>((size >> 24) & 0xff),
			static_cast<unsigned char>((size >> 16) & 0xff),
			static_cast<unsigned char>((size >> 8) & 0xff),
			static_cast<unsigned char>(size & 0xff) } };
	return sizeBytes;
}

template<class T>
uint32_t decodeSize(const T& sizeBytes) {
	uint32_t size = 0;
	// instead of ntohl:
	for (size_t i = 0; i < sizeof(size); ++i) {
		size <<= CHAR_BIT;
		size |= (uint32_t) sizeBytes[i];
	}
	return size;
}

template<class Ostream>
bool writeStringWithSizeOnStream(const std::string& outString, Ostream& stream) {
	uint32_t size = outString.size();
	ProtoSize sizeBytes = encodeSize(size);

	stream.write(reinterpret_cast<const char*>(sizeBytes.data()), sizeBytes.size());
	
	if(!stream.fail() && size > 0) {
		stream.write(outString.data(), size);
	}
	stream.flush();
	
	return !stream.fail();
}

template<class Istream>
bool readStringWithSizeFromStream(std::string& inString, Istream& stream) {
	ProtoSize sizeBytes;

	stream.read(reinterpret_cast<char*>(sizeBytes.data()), sizeBytes.size());

	bool isGood = stream.gcount() == sizeBytes.size(); 

	if(isGood) {
		uint32_t size = decodeSize(sizeBytes);
		
		inString.resize(size);
		
		if(size > 0) {
			stream.read(&inString[0], size);
			isGood = stream.gcount() == size;
		}
	}
	if(!isGood) {
		stream.setstate(std::ios::failbit);
	}
	return isGood;
}



template<typename Proto>
bool readProtoFromStream(Proto& proto, std::istream& stream) {
	std::string protoString;
	return readStringWithSizeFromStream(protoString, stream) && proto.ParseFromString(protoString);
}

template<typename Proto>
bool writeProtoOnStream(const Proto& proto, std::ostream& stream) {
	std::string protoString;	
	return proto.SerializeToString(&protoString) && writeStringWithSizeOnStream(protoString, stream);
}

#endif // STREAM_HPP

