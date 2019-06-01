// g++ test.c -I ../include libyaml-cpp.a -std=c++11

#include "yaml-cpp/yaml.h"
#include <iostream>
#include <fstream>

int main()
{
   YAML::Emitter out;
   std::string fileName = "test.yaml";
   std::ofstream my_file;
   my_file.open (fileName);

   out << YAML::BeginMap << YAML::Key << "GridSampleOption";
   out << YAML::BeginMap;
   out << YAML::Key << "number x";
   out << YAML::Value << 10;
   out << YAML::Key << "number y";
   out << YAML::Value << 20;
   out << YAML::EndMap;

   out << YAML::Key << "item";

   out << YAML::BeginSeq;

   out << YAML::BeginMap;
   out << YAML::Key << "info";
   out << YAML::Value << "vertex_id";
   out << YAML::Key << "gt";
   out << YAML::Flow;
   out << YAML::BeginSeq << 1 << 2 << 3 << 4 << YAML::EndSeq;
   out << YAML::Key << "idx";
   out << YAML::Flow;
   out << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;

   out << YAML::Key << "costmap";
   out << YAML::BeginSeq;
   out << YAML::Flow;
   out << YAML::BeginSeq << 1 << 2 << 3.1 << YAML::EndSeq;
   out << YAML::Flow;
   out << YAML::BeginSeq << 1 << 2 << 3.1 << YAML::EndSeq;
   out << YAML::Flow;
   out << YAML::BeginSeq << 1 << 2 << 3.1 << YAML::EndSeq;
   out << YAML::EndSeq;

   out << YAML::Key << "covtmap";
   out << YAML::BeginSeq;
   out << YAML::Flow;
   out << YAML::BeginSeq << 1 << 2 << 1 << 1<<  YAML::EndSeq;
   out << YAML::Flow;
   out << YAML::BeginSeq << 2 << 2 << 2 << 1<<  YAML::EndSeq;
   out << YAML::EndSeq;

   out << YAML::EndMap;

   out << YAML::BeginMap;
   out << YAML::Key << "info";
   out << YAML::Value << "vertex_id";
   out << YAML::Key << "gt";
   out << YAML::Flow;
   out << YAML::BeginSeq << 1 << 2 << 3 << 4 << YAML::EndSeq;
   out << YAML::Key << "idx";
   out << YAML::Flow;
   out << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;

   out << YAML::Key << "costmap";
   out << YAML::BeginSeq;
   out << YAML::Flow;
   out << YAML::BeginSeq << 1 << 2 << 3.1 << YAML::EndSeq;
   out << YAML::Flow;
   out << YAML::BeginSeq << 1 << 2 << 3.1 << YAML::EndSeq;
   out << YAML::Flow;
   out << YAML::BeginSeq << 1 << 2 << 3.1 << YAML::EndSeq;
   out << YAML::EndSeq;

   out << YAML::Key << "covtmap";
   out << YAML::BeginSeq;
   out << YAML::Flow;
   out << YAML::BeginSeq << 1 << 2 << 1 << 1<<  YAML::EndSeq;
   out << YAML::Flow;
   out << YAML::BeginSeq << 2 << 2 << 2 << 1<<  YAML::EndSeq;
   out << YAML::EndSeq;

   out << YAML::EndMap;

   out << YAML::EndSeq;

   out << YAML::EndMap;

   std::cout << "Here's the output YAML:\n" << out.c_str() << std::endl;
   my_file << out.c_str();
   my_file.close();
   return 0;
}
