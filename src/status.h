#ifndef MLO_STATUS_H
#define MLO_STATUS_H

namespace mlo {

class Status {
 public:
  Status() : code_(kOk) { }
  ~Status();

  Status(const Status& s) { code_ = s.code_; }
  void operator=(const Status& s) { code_ = s.code_; }

  static Status IOError() { return Status(kIOError); }
  static Status Ok() { return Status(); }

  bool IsOk() { return code_ == kOk; }
  bool IsIOError() { return code_ == kIOError; }

 private:
  enum Code {
    kOk,
    kIOError
  };

  Code code_;

  Status(Code code) : code_(code) { }
};

}

#endif
