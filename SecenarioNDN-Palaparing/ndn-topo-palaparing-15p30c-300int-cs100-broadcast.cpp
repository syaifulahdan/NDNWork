// ndn-congestion-topo-plugin.cpp

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ndnSIM-module.h"


using namespace ns3;
using ns3::ndn::StackHelper;
using ns3::ndn::AppHelper;
using ns3::ndn::GlobalRoutingHelper;
using ns3::ndn::StrategyChoiceHelper;

namespace ns3 {

int
main(int argc, char* argv[])
{
  CommandLine cmd;
  cmd.Parse(argc, argv);

  AnnotatedTopologyReader topologyReader("", 23);
  topologyReader.SetFileName("src/ndnSIM/examples/topologies/topo-palaparingv2.txt");
  topologyReader.Read();

  // Install NDN stack on all nodes
  ndn::StackHelper ndnHelper;
  ndnHelper.SetOldContentStore("ns3::ndn::cs::Lru", "MaxSize", "100");
  ndnHelper.SetDefaultRoutes(true);
  ndnHelper.InstallAll();




  // Installing global routing interface on all nodes
  ndn::GlobalRoutingHelper ndnGlobalRoutingHelper;
  ndnGlobalRoutingHelper.InstallAll();

  // Getting containers producer 1 / Consumer 1&2
  Ptr<Node> producer1 = Names::Find<Node>("medan");
  Ptr<Node> consumer1 = Names::Find<Node>("sabang");
  Ptr<Node> consumer2 = Names::Find<Node>("gunungsitoli");
  //----------------------------------------------

  // Getting containers producer 2 / Consumer 3&4
  Ptr<Node> producer2 = Names::Find<Node>("pekanbaru");
  Ptr<Node> consumer3 = Names::Find<Node>("lhokseumawe");
  Ptr<Node> consumer4 = Names::Find<Node>("batam");
  //----------------------------------------------
 
  // Getting containers producer 3 / Consumer 5&6
  Ptr<Node> producer3 = Names::Find<Node>("bengkalis");
  Ptr<Node> consumer5 = Names::Find<Node>("mentawai");
  Ptr<Node> consumer6 = Names::Find<Node>("kepmeranti");
  //----------------------------------------------

  // Getting containers producer 4 / Consumer 7&8
  Ptr<Node> producer4 = Names::Find<Node>("baturaja");
  Ptr<Node> consumer7 = Names::Find<Node>("bengkulu");
  Ptr<Node> consumer8 = Names::Find<Node>("lampung");
  //----------------------------------------------

  // Getting containers producer 5 / Consumer 9&10
  Ptr<Node> producer5 = Names::Find<Node>("palembang");
  Ptr<Node> consumer9 = Names::Find<Node>("pulaubangka");
  Ptr<Node> consumer10 = Names::Find<Node>("pagaralam");
  //----------------------------------------------

  // Getting containers producer 6 / Consumer 11&12  
  Ptr<Node> producer6 = Names::Find<Node>("ponorogo");
  Ptr<Node> consumer11 = Names::Find<Node>("purwokerto");
  Ptr<Node> consumer12 = Names::Find<Node>("cirebon");
  //----------------------------------------------
  
  // Getting containers producer 7 / Consumer 13&14  
  Ptr<Node> producer7 = Names::Find<Node>("surabaya");
  Ptr<Node> consumer13 = Names::Find<Node>("banyuwangi");
  Ptr<Node> consumer14 = Names::Find<Node>("palangkaraya");
  //----------------------------------------------

  // Getting containers producer 8 / Consumer 15&16  
  Ptr<Node> producer8 = Names::Find<Node>("bandung");
  Ptr<Node> consumer15 = Names::Find<Node>("malang");
  Ptr<Node> consumer16 = Names::Find<Node>("kseribu");
  //----------------------------------------------

  // Getting containers producer 9 / Consumer 17&18    
  Ptr<Node> producer9 = Names::Find<Node>("pontianak");
  Ptr<Node> consumer17 = Names::Find<Node>("semitau");
  Ptr<Node> consumer18 = Names::Find<Node>("ketapang");
  //----------------------------------------------
  
  // Getting containers producer 10 / Consumer 19&20    
  Ptr<Node> producer10 = Names::Find<Node>("banjarmasin");
  Ptr<Node> consumer19 = Names::Find<Node>("tebangan");
  Ptr<Node> consumer20 = Names::Find<Node>("balikpapan");
  //----------------------------------------------

  // Getting containers producer 11 / Consumer 21&22    
  Ptr<Node> producer11 = Names::Find<Node>("tarakan");
  Ptr<Node> consumer21 = Names::Find<Node>("gorontalo");
  Ptr<Node> consumer22 = Names::Find<Node>("nunukan");
  //----------------------------------------------

  // Getting containers producer 12 / Consumer 23&24    
  Ptr<Node> producer12 = Names::Find<Node>("ternate");
  Ptr<Node> consumer23 = Names::Find<Node>("talaud");
  Ptr<Node> consumer24 = Names::Find<Node>("pulaumorotai");
  //----------------------------------------------

  // Getting containers producer 13 / Consumer 25&26    
  Ptr<Node> producer13 = Names::Find<Node>("kotamobagu");
  Ptr<Node> consumer25 = Names::Find<Node>("parepare");
  Ptr<Node> consumer26 = Names::Find<Node>("banggai");
  //----------------------------------------------

 // Getting containers producer 14 / Consumer 27&28  
  Ptr<Node> producer14 = Names::Find<Node>("merauke");
  Ptr<Node> consumer27 = Names::Find<Node>("wamena");
  Ptr<Node> consumer28 = Names::Find<Node>("aru");
  //----------------------------------------------------- 

 // Getting containers producer 15 / Consumer 29&30  
  Ptr<Node> producer15 = Names::Find<Node>("jayapura");
  Ptr<Node> consumer29 = Names::Find<Node>("tolikara");
  Ptr<Node> consumer30 = Names::Find<Node>("rajaampat");
  //----------------------------------------------------- 


// Define 25 name prefixes
   std::string prefix1 = "/medan";
   std::string prefix2 = "/pekanbaru";
   std::string prefix3 = "/bengkalis";
   std::string prefix4 = "/baturaja";
   std::string prefix5 = "/palembang";
   std::string prefix6 = "/ponorogo";
   std::string prefix7 = "/surabaya";
   std::string prefix8 = "/bandung";
   std::string prefix9 = "/pontianak";
   std::string prefix10 = "/banjarmasin";
   std::string prefix11 = "/tarakan";
   std::string prefix12 = "/ternate";
   std::string prefix13 = "/kotamobagu";
   std::string prefix14 = "/merauke";
   std::string prefix15 = "/jayapura";

  

// Install different forwarding strategies for prefix1, prefix2
 ndn::StrategyChoiceHelper::InstallAll(prefix1, "/localhost/nfd/strategy/broadcast");
 ndn::StrategyChoiceHelper::InstallAll(prefix2, "/localhost/nfd/strategy/broadcast");
 ndn::StrategyChoiceHelper::InstallAll(prefix3, "/localhost/nfd/strategy/broadcast");
 ndn::StrategyChoiceHelper::InstallAll(prefix4, "/localhost/nfd/strategy/broadcast");
 ndn::StrategyChoiceHelper::InstallAll(prefix5, "/localhost/nfd/strategy/broadcast");
 ndn::StrategyChoiceHelper::InstallAll(prefix6, "/localhost/nfd/strategy/broadcast");
 ndn::StrategyChoiceHelper::InstallAll(prefix7, "/localhost/nfd/strategy/broadcast");
 ndn::StrategyChoiceHelper::InstallAll(prefix8, "/localhost/nfd/strategy/broadcast");
 ndn::StrategyChoiceHelper::InstallAll(prefix9, "/localhost/nfd/strategy/broadcast");
 ndn::StrategyChoiceHelper::InstallAll(prefix10, "/localhost/nfd/strategy/broadcast");
 ndn::StrategyChoiceHelper::InstallAll(prefix11, "/localhost/nfd/strategy/broadcast");
 ndn::StrategyChoiceHelper::InstallAll(prefix12, "/localhost/nfd/strategy/broadcast");
 ndn::StrategyChoiceHelper::InstallAll(prefix13, "/localhost/nfd/strategy/broadcast");
 ndn::StrategyChoiceHelper::InstallAll(prefix14, "/localhost/nfd/strategy/broadcast");
 ndn::StrategyChoiceHelper::InstallAll(prefix15, "/localhost/nfd/strategy/broadcast");

 

// Consumer
  ndn::AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
// Consumer will request /prefix/0, /prefix/1, ...
  consumerHelper.SetAttribute("Frequency", StringValue("500")); // 100 interests a second
// on the first consumer node install a Consumer application
// that will express interests in /dst consumer (1-30) namespace
  consumerHelper.SetPrefix(prefix1);  consumerHelper.Install(consumer1);
  consumerHelper.SetPrefix(prefix1);  consumerHelper.Install(consumer2);

  consumerHelper.SetPrefix(prefix2);  consumerHelper.Install(consumer3);
  consumerHelper.SetPrefix(prefix2);  consumerHelper.Install(consumer4);

  consumerHelper.SetPrefix(prefix3);  consumerHelper.Install(consumer5);
  consumerHelper.SetPrefix(prefix3);  consumerHelper.Install(consumer6);

  consumerHelper.SetPrefix(prefix4);  consumerHelper.Install(consumer7);
  consumerHelper.SetPrefix(prefix4);  consumerHelper.Install(consumer8);

  consumerHelper.SetPrefix(prefix5);  consumerHelper.Install(consumer9);
  consumerHelper.SetPrefix(prefix5);  consumerHelper.Install(consumer10);

  consumerHelper.SetPrefix(prefix6);  consumerHelper.Install(consumer11);
  consumerHelper.SetPrefix(prefix6);  consumerHelper.Install(consumer12);

  consumerHelper.SetPrefix(prefix7);  consumerHelper.Install(consumer13);
  consumerHelper.SetPrefix(prefix7);  consumerHelper.Install(consumer14);

  consumerHelper.SetPrefix(prefix8);  consumerHelper.Install(consumer15);
  consumerHelper.SetPrefix(prefix8);  consumerHelper.Install(consumer16);

  consumerHelper.SetPrefix(prefix9);  consumerHelper.Install(consumer17);
  consumerHelper.SetPrefix(prefix9);  consumerHelper.Install(consumer18);

  consumerHelper.SetPrefix(prefix10);  consumerHelper.Install(consumer19);
  consumerHelper.SetPrefix(prefix10);  consumerHelper.Install(consumer20);

  consumerHelper.SetPrefix(prefix11);  consumerHelper.Install(consumer21);
  consumerHelper.SetPrefix(prefix11);  consumerHelper.Install(consumer22);

  consumerHelper.SetPrefix(prefix12);  consumerHelper.Install(consumer23);
  consumerHelper.SetPrefix(prefix12);  consumerHelper.Install(consumer24);

  consumerHelper.SetPrefix(prefix13);  consumerHelper.Install(consumer25);
  consumerHelper.SetPrefix(prefix13);  consumerHelper.Install(consumer26);

  consumerHelper.SetPrefix(prefix14);  consumerHelper.Install(consumer27);
  consumerHelper.SetPrefix(prefix14);  consumerHelper.Install(consumer28);

  consumerHelper.SetPrefix(prefix15);  consumerHelper.Install(consumer29);
  consumerHelper.SetPrefix(prefix15);  consumerHelper.Install(consumer30);

  


  ndn::AppHelper producerHelper("ns3::ndn::Producer");
  producerHelper.SetAttribute("PayloadSize", StringValue("1024"));

  // Add /prefix1 to /prefix30 origins to ndn::GlobalRouter
ndnGlobalRoutingHelper.AddOrigins(prefix1, producer1);
  producerHelper.SetPrefix(prefix1);
  producerHelper.Install(producer1);

ndnGlobalRoutingHelper.AddOrigins(prefix2, producer2);
  producerHelper.SetPrefix(prefix2);  
  producerHelper.Install(producer2);

ndnGlobalRoutingHelper.AddOrigins(prefix3, producer3);
  producerHelper.SetPrefix(prefix3);  
  producerHelper.Install(producer3);

ndnGlobalRoutingHelper.AddOrigins(prefix4, producer4);
  producerHelper.SetPrefix(prefix4);  
  producerHelper.Install(producer4);

ndnGlobalRoutingHelper.AddOrigins(prefix5, producer5);
  producerHelper.SetPrefix(prefix5);  
  producerHelper.Install(producer5);

ndnGlobalRoutingHelper.AddOrigins(prefix6, producer6);
  producerHelper.SetPrefix(prefix6);  
  producerHelper.Install(producer6);

ndnGlobalRoutingHelper.AddOrigins(prefix7, producer7);
  producerHelper.SetPrefix(prefix7);  
  producerHelper.Install(producer7);

ndnGlobalRoutingHelper.AddOrigins(prefix8, producer8);
  producerHelper.SetPrefix(prefix8);  
  producerHelper.Install(producer8);

ndnGlobalRoutingHelper.AddOrigins(prefix9, producer9);
  producerHelper.SetPrefix(prefix9);  
  producerHelper.Install(producer9);

ndnGlobalRoutingHelper.AddOrigins(prefix10, producer10);
  producerHelper.SetPrefix(prefix10);  
  producerHelper.Install(producer10);

ndnGlobalRoutingHelper.AddOrigins(prefix11, producer11);
  producerHelper.SetPrefix(prefix11);  
  producerHelper.Install(producer11);

ndnGlobalRoutingHelper.AddOrigins(prefix12, producer12);
  producerHelper.SetPrefix(prefix12);  
  producerHelper.Install(producer12);

ndnGlobalRoutingHelper.AddOrigins(prefix13, producer13);
  producerHelper.SetPrefix(prefix13);  
  producerHelper.Install(producer13);

ndnGlobalRoutingHelper.AddOrigins(prefix14, producer14);
  producerHelper.SetPrefix(prefix14);  
  producerHelper.Install(producer14);

ndnGlobalRoutingHelper.AddOrigins(prefix15, producer15);
  producerHelper.SetPrefix(prefix15);  
  producerHelper.Install(producer15);



  
  // Calculate and install FIBs
  //ndn::GlobalRoutingHelper::CalculateRoutes();

  ndn::AppDelayTracer::InstallAll("/home/bertopeng17/ndnSIM/ns-3/data-tracer-thesis/Delay-15p30c-broadcast-5s-500interest.txt");
  L2RateTracer::InstallAll("/home/bertopeng17/ndnSIM/ns-3/data-tracer-thesis/L2-15p30c-broadcast-5s-500interest.txt");
  ndn::L3RateTracer::InstallAll("/home/bertopeng17/ndnSIM/ns-3/data-tracer-thesis/L3-15p30c-broadcast-5s-500interest.txt");


  Simulator::Stop(Seconds(5.0));
  Simulator::Run();
  Simulator::Destroy();

  return 0;
}

} // namespace ns3

int
main(int argc, char* argv[])
{
  return ns3::main(argc, argv);
}
