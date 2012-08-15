#ifndef MLO_STATUS_H
#define MLO_STATUS_H

namespace falconer {

// TODO: move impl to status.cpp
class Status {
 public:
  Status() : code_(kOk) {}
  ~Status();

  Status(const Status& s) { code_ = s.code_; }
  void operator=(const Status& s) { code_ = s.code_; }

  static Status IoError() { return Status(kIoError); }
  static Status Ok() { return Status(); }

  bool ok() { return code_ == kOk; }
  bool IsNotFound() { return code_ == kIoError; }

 private:
  enum Code {
    kOk,
    kIoError
  };

  Code code_;

  Status(Code code) : code_(code) {}
};

}

#endif
