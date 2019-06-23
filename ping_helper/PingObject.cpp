
//#include "Ping.hpp"
#include "PingObject.hpp"

namespace sstd{

PingObject::PingObject(QObject * argParent ){

}

class GlobalPingObject{
   // boost::asio::io_context thisContex;
   // public:
   // inline auto & getContex(){
   //     return thisContex;
   // }
   // inline GlobalPingObject(){}
   // inline static auto & instance(){
   //     static GlobalPingObject globalAns  ;
   //     return globalAns;
   // }
};

void PingObject::start( const QString & arg ){
   // assert ( !thisPing );
   // thisSource = arg.toUtf8 ();
   // thisPing = new Ping(GlobalPingObject::instance ().getContex (),
   //                  thisSource.constData());
}

PingObject::~PingObject(){
   // delete thisPing;
}

}/*namespace sstd*/

















