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
  topologyReader.SetFileName("src/ndnSIM/examples/topologies/topo-palaparing.txt");
  topologyReader.Read();

  // Install NDN stack on all nodes
  ndn::StackHelper ndnHelper;
  ndnHelper.SetOldContentStore("ns3::ndn::cs::Lru", "MaxSize", "1000");
  ndnHelper.SetDefaultRoutes(true);
  ndnHelper.InstallAll();


  // Installing global routing interface on all nodes
  ndn::GlobalRoutingHelper ndnGlobalRoutingHelper;
  ndnGlobalRoutingHelper.InstallAll();

  // Getting containers for the consumer/producer
  Ptr<Node> consumer1 = Names::Find<Node>("sabang");
  Ptr<Node> consumer2 = Names::Find<Node>("lhokseumawe");
  Ptr<Node> consumer3 = Names::Find<Node>("mentawai");
  Ptr<Node> consumer4 = Names::Find<Node>("bengkulu");
  Ptr<Node> consumer5 = Names::Find<Node>("lampung");
  Ptr<Node> consumer6 = Names::Find<Node>("purwokerto");
  Ptr<Node> consumer7 = Names::Find<Node>("jogjakarta");
  Ptr<Node> consumer8 = Names::Find<Node>("kseribu");
  Ptr<Node> consumer9 = Names::Find<Node>("semitau");
  Ptr<Node> consumer10 = Names::Find<Node>("banjarmasin");
  Ptr<Node> consumer11 = Names::Find<Node>("balikpapan");
  Ptr<Node> consumer12 = Names::Find<Node>("gorontalo");
  Ptr<Node> consumer13 = Names::Find<Node>("talaud");
  Ptr<Node> consumer14 = Names::Find<Node>("parepare");
  Ptr<Node> consumer15 = Names::Find<Node>("probolinggo");
  Ptr<Node> consumer16 = Names::Find<Node>("denpasar");
  Ptr<Node> consumer17 = Names::Find<Node>("pulaurote");
  Ptr<Node> consumer18 = Names::Find<Node>("kendari");
  Ptr<Node> consumer19 = Names::Find<Node>("ambon");
  Ptr<Node> consumer20 = Names::Find<Node>("dogiyai");
  Ptr<Node> consumer21 = Names::Find<Node>("tolikara");
  Ptr<Node> consumer22 = Names::Find<Node>("merauke");
  Ptr<Node> consumer23 = Names::Find<Node>("wakatobi");
  Ptr<Node> consumer24 = Names::Find<Node>("pontianak");
  Ptr<Node> consumer25 = Names::Find<Node>("serang");
  Ptr<Node> consumer26 = Names::Find<Node>("batam");
  Ptr<Node> consumer27 = Names::Find<Node>("selayar");
  Ptr<Node> consumer28 = Names::Find<Node>("jambi");
  Ptr<Node> consumer29 = Names::Find<Node>("poso");
  Ptr<Node> consumer30 = Names::Find<Node>("ende");

  Ptr<Node> producer1 = Names::Find<Node>("medan");
  Ptr<Node> producer2 = Names::Find<Node>("pekanbaru");
  Ptr<Node> producer3 = Names::Find<Node>("bengkalis");
  Ptr<Node> producer4 = Names::Find<Node>("baturaja");
  Ptr<Node> producer5 = Names::Find<Node>("palembang");
  Ptr<Node> producer6 = Names::Find<Node>("ponorogo");
  Ptr<Node> producer7 = Names::Find<Node>("surabaya");
  Ptr<Node> producer8 = Names::Find<Node>("bandung");
  Ptr<Node> producer9 = Names::Find<Node>("ketapang");
  Ptr<Node> producer10 = Names::Find<Node>("tebangan");
  Ptr<Node> producer11 = Names::Find<Node>("tarakan");
  Ptr<Node> producer12 = Names::Find<Node>("ternate");
  Ptr<Node> producer13 = Names::Find<Node>("kotamobagu");
  Ptr<Node> producer14 = Names::Find<Node>("kupang");
  Ptr<Node> producer15 = Names::Find<Node>("mataram");
  Ptr<Node> producer16 = Names::Find<Node>("bima");
  Ptr<Node> producer17 = Names::Find<Node>("larantuka");
  Ptr<Node> producer18 = Names::Find<Node>("fakfak");
  Ptr<Node> producer19 = Names::Find<Node>("timika");
  Ptr<Node> producer20 = Names::Find<Node>("memberamoraya");
  Ptr<Node> producer21 = Names::Find<Node>("jayapura");
  Ptr<Node> producer22 = Names::Find<Node>("pegbintang");
  Ptr<Node> producer23 = Names::Find<Node>("bombana");
  Ptr<Node> producer24 = Names::Find<Node>("jakarta");
  Ptr<Node> producer25 = Names::Find<Node>("pulaubelitung");
  Ptr<Node> producer26 = Names::Find<Node>("natuna");
  Ptr<Node> producer27 = Names::Find<Node>("kutaibarat");
  Ptr<Node> producer28 = Names::Find<Node>("padang");
  Ptr<Node> producer29 = Names::Find<Node>("manado");
  Ptr<Node> producer30 = Names::Find<Node>("donggala");

// Define 30 name prefixes
  std::string prefix1 = "/medan";
  std::string prefix2 = "/pekanbaru";
  std::string prefix3 = "/bengkalis";
  std::string prefix4 = "/baturaja";
  std::string prefix5 = "/palembang";
  std::string prefix6 = "/ponorogo";
  std::string prefix7 = "/surabaya";
  std::string prefix8 = "/bandung";
  std::string prefix9 = "/ketapang";
  std::string prefix10 = "tebangan";
  std::string prefix11 = "/tarakan";
  std::string prefix12 = "/ternate";
  std::string prefix13 = "/kotamobagu";
  std::string prefix14 = "/kupang";
  std::string prefix15 = "/mataram";
  std::string prefix16 = "/bima";
  std::string prefix17 = "/larantuka";
  std::string prefix18 = "/fakfak";
  std::string prefix19 = "/timika";
  std::string prefix20 = "/membramoraya";
  std::string prefix21 = "/jayapura";
  std::string prefix22 = "/pegbintang";
  std::string prefix23 = "/bombana";
  std::string prefix24 = "/jakarta";
  std::string prefix25 = "/pulaubelitung";
  std::string prefix26 = "/natuna";
  std::string prefix27 = "/kutaibarat";
  std::string prefix28 = "/padang";
  std::string prefix29 = "/manado";
  std::string prefix30 = "/donggala";



  

// Install different forwarding strategies for prefix1, prefix2
 ndn::StrategyChoiceHelper::InstallAll(prefix1, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix2, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix3, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix4, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix5, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix6, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix7, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix8, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix9, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix10, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix11, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix12, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix13, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix14, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix15, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix16, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix17, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix18, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix19, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix21, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix22, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix23, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix24, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix25, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix26, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix27, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix28, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix29, "/localhost/nfd/strategy/best-route");
 ndn::StrategyChoiceHelper::InstallAll(prefix30, "/localhost/nfd/strategy/best-route");
 

// Consumer
  ndn::AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
// Consumer will request /prefix/0, /prefix/1, ...
  consumerHelper.SetAttribute("Frequency", StringValue("100")); // 100 interests a second
// on the first consumer node install a Consumer application
// that will express interests in /dst consumer (1-30) namespace
  consumerHelper.SetPrefix(prefix1);  consumerHelper.Install(consumer1);
  consumerHelper.SetPrefix(prefix2);  consumerHelper.Install(consumer2);
  consumerHelper.SetPrefix(prefix3);  consumerHelper.Install(consumer3);
  consumerHelper.SetPrefix(prefix4);  consumerHelper.Install(consumer4);
  consumerHelper.SetPrefix(prefix5);  consumerHelper.Install(consumer5);
  consumerHelper.SetPrefix(prefix6);  consumerHelper.Install(consumer6);
  consumerHelper.SetPrefix(prefix7);  consumerHelper.Install(consumer7);
  consumerHelper.SetPrefix(prefix8);  consumerHelper.Install(consumer8);
  consumerHelper.SetPrefix(prefix9);  consumerHelper.Install(consumer9);
  consumerHelper.SetPrefix(prefix10);  consumerHelper.Install(consumer10);
  consumerHelper.SetPrefix(prefix11);  consumerHelper.Install(consumer11);
  consumerHelper.SetPrefix(prefix12);  consumerHelper.Install(consumer12);
  consumerHelper.SetPrefix(prefix13);  consumerHelper.Install(consumer13);
  consumerHelper.SetPrefix(prefix14);  consumerHelper.Install(consumer14);
  consumerHelper.SetPrefix(prefix15);  consumerHelper.Install(consumer15);
  consumerHelper.SetPrefix(prefix16);  consumerHelper.Install(consumer16);
  consumerHelper.SetPrefix(prefix17);  consumerHelper.Install(consumer17);
  consumerHelper.SetPrefix(prefix18);  consumerHelper.Install(consumer18);
  consumerHelper.SetPrefix(prefix19);  consumerHelper.Install(consumer19);
  consumerHelper.SetPrefix(prefix20);  consumerHelper.Install(consumer20);

  consumerHelper.SetPrefix(prefix21);  consumerHelper.Install(consumer21);
  consumerHelper.SetPrefix(prefix22);  consumerHelper.Install(consumer22);
  consumerHelper.SetPrefix(prefix23);  consumerHelper.Install(consumer23);
  consumerHelper.SetPrefix(prefix24);  consumerHelper.Install(consumer24);
  consumerHelper.SetPrefix(prefix25);  consumerHelper.Install(consumer25);
  consumerHelper.SetPrefix(prefix26);  consumerHelper.Install(consumer26);
  consumerHelper.SetPrefix(prefix27);  consumerHelper.Install(consumer27);
  consumerHelper.SetPrefix(prefix28);  consumerHelper.Install(consumer28);
  consumerHelper.SetPrefix(prefix29);  consumerHelper.Install(consumer29);
  consumerHelper.SetPrefix(prefix30);  consumerHelper.Install(consumer30);

  


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
  ndnGlobalRoutingHelper.AddOrigins(prefix16, producer16);
  producerHelper.SetPrefix(prefix16);
  producerHelper.Install(producer16);
  ndnGlobalRoutingHelper.AddOrigins(prefix17, producer17);
  producerHelper.SetPrefix(prefix17);  
  producerHelper.Install(producer17);
  ndnGlobalRoutingHelper.AddOrigins(prefix18, producer18);  
  producerHelper.SetPrefix(prefix18);  
  producerHelper.Install(producer18);
  ndnGlobalRoutingHelper.AddOrigins(prefix19, producer19);
  producerHelper.SetPrefix(prefix19);
  producerHelper.Install(producer19);
  ndnGlobalRoutingHelper.AddOrigins(prefix20, producer20);
  producerHelper.SetPrefix(prefix20);
  producerHelper.Install(producer20);

ndnGlobalRoutingHelper.AddOrigins(prefix21, producer21);
  producerHelper.SetPrefix(prefix21);
  producerHelper.Install(producer21);

ndnGlobalRoutingHelper.AddOrigins(prefix22, producer22);
  producerHelper.SetPrefix(prefix22);
  producerHelper.Install(producer22);

ndnGlobalRoutingHelper.AddOrigins(prefix23, producer23);
  producerHelper.SetPrefix(prefix23);
  producerHelper.Install(producer23);

ndnGlobalRoutingHelper.AddOrigins(prefix24, producer24);
  producerHelper.SetPrefix(prefix24);
  producerHelper.Install(producer24);

ndnGlobalRoutingHelper.AddOrigins(prefix25, producer25);
  producerHelper.SetPrefix(prefix25);
  producerHelper.Install(producer25);

ndnGlobalRoutingHelper.AddOrigins(prefix26, producer26);
  producerHelper.SetPrefix(prefix26);
  producerHelper.Install(producer26);

ndnGlobalRoutingHelper.AddOrigins(prefix27, producer27);
  producerHelper.SetPrefix(prefix27);
  producerHelper.Install(producer27);

ndnGlobalRoutingHelper.AddOrigins(prefix28, producer28);
  producerHelper.SetPrefix(prefix28);
  producerHelper.Install(producer28);

ndnGlobalRoutingHelper.AddOrigins(prefix29, producer29);
  producerHelper.SetPrefix(prefix29);
  producerHelper.Install(producer29);

ndnGlobalRoutingHelper.AddOrigins(prefix30, producer30);
  producerHelper.SetPrefix(prefix30);
  producerHelper.Install(producer30);
  
  // Calculate and install FIBs
  ndn::GlobalRoutingHelper::CalculateRoutes();

  ndn::AppDelayTracer::InstallAll("/home/bertopeng17/ndnSIM/ns-3/data-tracer-thesis/Delay-broadcast-5s-100interest.txt");
  L2RateTracer::InstallAll("/home/bertopeng17/ndnSIM/ns-3/data-tracer-thesis/L2-broadcast-5s-100interest.txt");
  ndn::L3RateTracer::InstallAll("/home/bertopeng17/ndnSIM/ns-3/data-tracer-thesis/L3-broadcast-5s-100interest.txt");


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
