#ifndef PAPER_ANALYSIS_ERROR_CODE_H
#define PAPER_ANALYSIS_ERROR_CODE_H

#include <string>
#include <map>
#include <cassert>

#include <config.h>


namespace qierr {

typedef int error_code;

  /**
 * @file   error_code.h
 * @author qijiabao
 * @date   2023.8.21
 *
 * @brief
 *         通用错误码定义及实现
 *
 * @note
 *         1、错误码从0开始计算，顺序添加。
 *         2、实际使用时，除E_OK外，错误码可以是负数(需要手工添加'-')，也可以是正数。
 *         3、错误码可以是任何数字，但不在枚举之列则显示未知错误码。
 *
 * @log
 *
 */

class Error
{
public:
  Error(int value, const std::string& str)
  {
    m_value = value;
    m_message = str;
#ifdef _DEBUG
    ErrorMap::iterator found = GetErrorMap().find(value);
    if (found != GetErrorMap().end())
      assert(found->second == m_message);
#endif
    GetErrorMap()[m_value] = m_message;
  }

  // auto-cast Error to integer error code
  operator int() { return m_value; }

private:
  int m_value;
  std::string m_message;

  typedef std::map<int, std::string> ErrorMap;
  static ErrorMap& GetErrorMap()
  {
    static ErrorMap errMap;
    return errMap;
  }

public:

  static std::string GetErrorString(int value)
  {
    ErrorMap::iterator found = GetErrorMap().find(value);
    if (found == GetErrorMap().end())
    {
      assert(false);
      return "";
    }
    else
    {
      return found->second;
    }
  }
};

enum errorcode {
  E_OK_CODE = 0,         ///< 成功
  E_FAIL_CODE,           ///< 一般性错误
  E_INNER_CODE,          ///< 内部错误（一般在同一个模块内使用，不对外公开
  E_POINTER_CODE,        ///< 非法指针
  E_INVALARG_CODE,       ///< 非法参数
  E_NOTIMPL_CODE = 5,    ///< 功能未实现
  E_OUTOFMEM_CODE,       ///< 内存申请失败/内存不足
  E_BUFERROR_CODE,       ///< 缓冲区错误（不足，错乱）
  E_PERM_CODE,           ///< 权限不足，访问未授权的对象
  E_TIMEOUT_CODE,        ///< 超时
  E_NOTINIT_CODE = 10,   ///< 未初始化
  E_INITFAIL_CODE,       ///< 初始化失败
  E_ALREADY_CODE,        ///< 已初始化，已经在运行
  E_INPROGRESS_CODE,     ///< 已在运行、进行状态
  E_EXIST_CODE,          ///< 申请资源对象(如文件或目录)已存在
  E_NOTEXIST_CODE,       ///< 资源对象(如文件或目录)、命令、设备等不存在
  E_BUSY_CODE,           ///< 设备或资源忙（资源不可用）
  E_FULL_CODE,           ///< 设备/资源已满
  E_EMPTY_CODE,          ///< 对象/内存/内容为空
  E_OPENFAIL_CODE,       ///< 资源对象(如文件或目录、socket)打开失败
  E_READFAIL_CODE,       ///< 资源对象(如文件或目录、socket)读取、接收失败
  E_WRITEFAIL_CODE,      ///< 资源对象(如文件或目录、socket)写入、发送失败
  E_DELFAIL_CODE,        ///< 资源对象(如文件或目录、socket)删除、关闭失败
  E_ILLEGAL_CODE,        ///< 资源对象(如文件、目录、socket、设备等)非法
  E_CODECFAIL_CODE,      ///< 加解密、编码解密失败
  E_CRC_FAIL_CODE,       ///< crc校验错误
  E_TOOMANY_CODE,        ///< 消息、缓冲区、内容太多
  E_TOOSMALL_CODE,       ///< 消息、缓冲区、内容太少
  E_NETNOTREACH_CODE,    ///< 网络不可达（无路由，网关错误）
  E_NETDOWN_CODE,        ///< 网络不可用（断网）
  E_XMLEXCEPTION_CODE,   ///< xml解析错误
  E_JSONEXCEPTION_CODE,  ///< json解析错误
  E_FILEEXCEPTION_CODE,  ///< 文件操作错误
  E_NETEXCEPTION_CODE,   ///< 网络操作错误
  E_DBEXCEPTION_CODE,    ///< 数据库操作错误
  E_DOMEXCEPTTON_CODE,   ///< dom操作错误
  E_ILLEGAL_FILE_CODE,   ///< 非法文件
  E_ILLEGAL_PATH_CODE,   ///< 非法路径

  E_UNKNOWN_CODE = 100,  ///< 未知错误


  // more...

  E_END,            ///< 占位，无实际作用
};

static Error E_OK(E_OK_CODE, "Success");
static Error E_FAIL(E_FAIL_CODE, "General Failed");
static Error E_INNER(E_INNER_CODE, "Internal error");
static Error E_POINTER(E_POINTER_CODE, "Invalid Pointer");
static Error E_INVALARG(E_INVALARG_CODE, "Invalid argument");
static Error E_NOTIMPL(E_NOTIMPL_CODE, "Not implemented");
static Error E_OUTOFMEM(E_OUTOFMEM_CODE, "Out of memory");
static Error E_BUFERROR(E_BUFERROR_CODE, "Buffer error");
static Error E_PERM(E_PERM_CODE, "Permission denied");
static Error E_TIMEOUT(E_TIMEOUT_CODE, "Timed out");
static Error E_NOTINIT(E_NOTINIT_CODE, "Object not init");
static Error E_INITFAIL(E_INITFAIL_CODE, "Object init failed");
static Error E_ALREADY(E_ALREADY_CODE, "Operation already in progress");
static Error E_INPROGRESS(E_INPROGRESS_CODE, "Operation now in progress");
static Error E_EXIST(E_EXIST_CODE, "Object exist");
static Error E_NOTEXIST(E_NOTEXIST_CODE, "Object not exist");
static Error E_BUSY(E_BUSY_CODE, "Device or resource busy");
static Error E_FULL(E_FULL_CODE, "Device or resource full");
static Error E_EMPTY(E_EMPTY_CODE, "Device or resource empty");
static Error E_OPENFAIL(E_OPENFAIL_CODE, "Device or resource open failed");
static Error E_READFAIL(E_READFAIL_CODE, "Device or resource read failed");
static Error E_WRITEFAIL(E_WRITEFAIL_CODE, "Device or resource write failed");
static Error E_DELFAIL(E_DELFAIL_CODE, "Device or resource delete failed");
static Error E_ILLEGAL(E_ILLEGAL_CODE, "Device or resource illegal");
static Error E_CODECFAIL(E_CODECFAIL_CODE, "Encode or decode failed");
static Error E_CRC_FAIL(E_CRC_FAIL_CODE, "CRC failed");
static Error E_TOOMANY(E_TOOMANY_CODE, "Object too many");
static Error E_TOOSMALL(E_TOOSMALL_CODE, "Object too small");
static Error E_NETNOTREACH(E_NETNOTREACH_CODE, "Network is unreachable");
static Error E_NETDOWN(E_NETDOWN_CODE, "Network is down");
static Error E_XMLEXCEPTION(E_XMLEXCEPTION_CODE, "XML exception");
static Error E_JSONEXCEPTION(E_JSONEXCEPTION_CODE, "JSON exception");
static Error E_FILEEXCEPTION(E_FILEEXCEPTION_CODE, "File exception");
static Error E_NETEXCEPTION(E_NETEXCEPTION_CODE, "Network exception");
static Error E_DBEXCEPTION(E_DBEXCEPTION_CODE, "Database exception");
static Error E_DOMEXCEPTTON(E_DOMEXCEPTTON_CODE, "DOM exception");
static Error E_ILLEGAL_FILE(E_ILLEGAL_FILE_CODE, "Illegal file");
static Error E_ILLEGAL_PATH(E_ILLEGAL_PATH_CODE, "Illegal path");
static Error E_UNKNOWN(E_UNKNOWN_CODE, "Unknown error");

}; // namespace qi

#endif //PAPER_ANALYSIS_ERROR_CODE_H
