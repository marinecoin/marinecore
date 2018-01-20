#ifndef _MARINECORERPC_H_
#define _MARINECORERPC_H_ 1

#include <string>
#include <list>
#include <map>

#include "json/json_spirit_reader_template.h"
#include "json/json_spirit_writer_template.h"
#include "json/json_spirit_utils.h"

json_spirit::Object JSONRPCError(int code, const std::string& message);

void ThreadRPCServer(void* parg);
int CommandLineRPC(int argc, char *argv[]);

json_spirit::Array RPCConvertValues(const std::string &strMethod, const std::vector<std::string> &strParams);

void RPCTypeCheck(const json_spirit::Array& params,
                  const std::list<json_spirit::Value_type>& typesExpected);
void RPCTypeCheck(const json_spirit::Object& o,
                  const std::map<std::string, json_spirit::Value_type>& typesExpected);

typedef json_spirit::Value(*rpcfn_type)(const json_spirit::Array& params, bool fHelp);

class CRPCCommand
{
public:
    std::string name;
    rpcfn_type actor;
    bool okSafeMode;
};

class CRPCTable
{
private:
    std::map<std::string, const CRPCCommand*> mapCommands;
public:
    CRPCTable();
    const CRPCCommand* operator[](std::string name) const;
    std::string help(std::string name) const;

    json_spirit::Value execute(const std::string &method, const json_spirit::Array &params) const;
};

extern const CRPCTable tableRPC;

#endif
