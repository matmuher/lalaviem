#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"

#include "sim.h"

#define FILE_IR "app_handmade.ll"

using namespace llvm;

int main() {
    LLVMContext Ctx;

    Module *module = new Module("app.c", Ctx);
    IRBuilder<> Builder(Ctx);
    
    auto toInt = [&Builder](int num){return Builder.getInt32(num);};

    /* [Declarations]
    [X] declare void @simPutSpring(i32, i32, i32, i32)

    [X] declare void @simFlush(...)

    [X] declare i32 @simGetPixel(i32, i32)

    [X] declare i32 @simGetLength(i32, i32)

    [X] declare i32 @simRand(i32, i32)

    [X] declare void @simPutPixel(i32, i32, i32)

    declare i32 @simMixColors(i32, i32, i32, i32)
    */

    Type *VoidT = Type::getVoidTy(Ctx);
    Type *IntT = Type::getInt32Ty(Ctx);

    // declare void @simPutSpring(i32, i32, i32, i32)
    FunctionType *simPutSpringT = 
        FunctionType::get(VoidT, {IntT, IntT, IntT, IntT}, false);
    FunctionCallee simPutSpringF =
        module->getOrInsertFunction("simPutSpring", simPutSpringT);

    // declare void @simFlush(...)
    FunctionType *simFlushT = 
        FunctionType::get(VoidT, {VoidT}, false);
    FunctionCallee simFlushF =
        module->getOrInsertFunction("simFlush", simFlushT);

    // declare i32 @simGetPixel(i32, i32)
    FunctionType *simGetPixelT =
        FunctionType::get(IntT, {IntT, IntT}, false);
    FunctionCallee simGetPixelF =
        module->getOrInsertFunction("simGetPixel", simGetPixelT);

    // declare i32 @simGetLength(i32, i32)
    FunctionType *simGetLengthT =
        FunctionType::get(IntT, {IntT, IntT}, false);
    FunctionCallee simGetLengthF =
        module->getOrInsertFunction("simGetLength", simGetLengthT);

    // declare i32 @simRand(i32, i32)
    FunctionType *simRandT =
        FunctionType::get(IntT, {IntT, IntT}, false);
    FunctionCallee simRandF =
        module->getOrInsertFunction("simRand", simRandT);

    // declare void @simPutPixel(i32, i32, i32)
    FunctionType *simPutPixelT =
        FunctionType::get(VoidT, {IntT, IntT, IntT}, false);
    FunctionCallee simPutPixelF =
        module->getOrInsertFunction("simPutPixel", simPutPixelT);

    // declare i32 @simMixColors(i32, i32, i32, i32)
    FunctionType *simMixColorsT =
        FunctionType::get(IntT, {IntT, IntT, IntT, IntT}, false);
    FunctionCallee simMixColorsF =
        module->getOrInsertFunction("simMixColors", simMixColorsT);

    // [Definitions]
    /*
    define void @app() #0 {
        tail call void @simPutSpring(i32  10, i32  2, i32  -16711936, i32  1) #2
        tail call void @simPutSpring(i32  25, i32  20, i32  -16711936, i32  1) #2
        tail call void @simPutSpring(i32  50, i32  30, i32  -16711936, i32  1) #2
        tail call void @simPutSpring(i32  75, i32  50, i32  -16711936, i32  1) #2
        tail call void @simPutSpring(i32  100, i32  10, i32  -16711936, i32  1) #2
        tail call void (...) @simFlush() #2
        br label %1

        1:                                                ; preds = %0, %7
        %2 = phi i32 [ 0, %0 ], [ %8, %7 ]
        br label %4

        3:                                                ; preds = %7
        ret void

        4:                                                ; preds = %1, %10
        %5 = phi i32 [ 0, %1 ], [ %11, %10 ]
        %6 = sub nuw nsw i32 64, %5
        br label %13

        7:                                                ; preds = %10
        tail call void (...) @simFlush() #2
        %8 = add nuw nsw i32 %2, 1
        %9 = icmp eq i32 %8, 200
        br i1 %9, label %3, label %1, !llvm.loop !5

        10:                                               ; preds = %32
        %11 = add nuw nsw i32 %5, 1
        %12 = icmp eq i32 %11, 64
        br i1 %12, label %7, label %4, !llvm.loop !7

        13:                                               ; preds = %4, %32
        %14 = phi i32 [ 0, %4 ], [ %33, %32 ]
        %15 = tail call i32 @simGetPixel(i32  %14, i32  %5) #2
        %16 = tail call i32 @simGetLength(i32  %14, i32  %5) #2
        %17 = icmp eq i32 %15, -16711936
        %18 = icmp sgt i32 %16, 0
        %19 = select i1 %17, i1 %18, i1 false
        br i1 %19, label %20, label %32

        20:                                               ; preds = %13
        %21 = tail call i32 @simRand(i32  -1, i32  1) #2
        %22 = tail call i32 @simRand(i32  1, i32  1) #2
        %23 = mul nsw i32 %21, %16
        %24 = add nsw i32 %23, %14
        %25 = mul nsw i32 %22, %16
        %26 = add nsw i32 %25, %5
        %27 = tail call i32 @simMixColors(i32  -16711936, i32  -16751104, i32  %5, i32  %6) #2
        tail call void @simPutPixel(i32  %24, i32  %26, i32  %27) #2
        %28 = tail call i32 @simRand(i32  -1, i32  1) #2
        %29 = mul nsw i32 %28, %16
        %30 = add nsw i32 %29, %14
        %31 = tail call i32 @simRand(i32  1, i32  %16) #2
        tail call void @simPutSpring(i32  %30, i32  %26, i32  -16711936, i32  %31) #2
        br label %32

        32:                                               ; preds = %20, %13
        %33 = add nuw nsw i32 %14, 1
        %34 = icmp eq i32 %33, 128
        br i1 %34, label %10, label %13, !llvm.loop !8
    }
    */

    FunctionType *appT = FunctionType::get(VoidT, false);
    Function *appDef =
        Function::Create(appT, Function::ExternalLinkage, "app", module);

    BasicBlock *BB0 = BasicBlock::Create(Ctx, "", appDef);
    BasicBlock *BB1 = BasicBlock::Create(Ctx, "", appDef);
    BasicBlock *BB3 = BasicBlock::Create(Ctx, "", appDef);
    BasicBlock *BB4 = BasicBlock::Create(Ctx, "", appDef);
    BasicBlock *BB7 = BasicBlock::Create(Ctx, "", appDef);
    BasicBlock *BB10 = BasicBlock::Create(Ctx, "", appDef);
    BasicBlock *BB13 = BasicBlock::Create(Ctx, "", appDef);
    BasicBlock *BB20 = BasicBlock::Create(Ctx, "", appDef);
    BasicBlock *BB32 = BasicBlock::Create(Ctx, "", appDef);

    // #0
    Builder.SetInsertPoint(BB0);
    //    tail call void @simPutSpring(i32  10, i32  2, i32  -16711936, i32  1)
    Builder.CreateCall(simPutSpringF, {toInt(10), toInt(2), toInt(-16711936), toInt(1)});

    //     tail call void @simPutSpring(i32  25, i32  20, i32  -16711936, i32  1)
    Builder.CreateCall(simPutSpringF, {toInt(25), toInt(20), toInt(-16711936), toInt(1)});
    
    //     tail call void @simPutSpring(i32  50, i32  30, i32  -16711936, i32  1) #2
    Builder.CreateCall(simPutSpringF, {toInt(50), toInt(30), toInt(-16711936), toInt(1)});

    //     tail call void @simPutSpring(i32  75, i32  50, i32  -16711936, i32  1) #2
    Builder.CreateCall(simPutSpringF, {toInt(75), toInt(50), toInt(-16711936), toInt(1)});

    //     tail call void @simPutSpring(i32  100, i32  10, i32  -16711936, i32  1) #2
    Builder.CreateCall(simPutSpringF, {toInt(100), toInt(10), toInt(-16711936), toInt(1)});

    //     tail call void (...) @simFlush() #2
    Builder.CreateCall(simFlushF);

    //     br label %1
    Builder.CreateBr(BB1);

    //     1:                                                ; preds = %0, %7
    Builder.SetInsertPoint(BB1);

    //     %2 = phi i32 [ 0, %0 ], [ %8, %7 ]
    PHINode *val2 = Builder.CreatePHI(IntT, 2);

    //     br label %4
    Builder.CreateBr(BB4);

    //     3:                                                ; preds = %7
    Builder.SetInsertPoint(BB3);

    //     ret void
    Builder.CreateRetVoid();

    //     4:                                                ; preds = %1, %10
    Builder.SetInsertPoint(BB4);

    //     %5 = phi i32 [ 0, %1 ], [ %11, %10 ]
    PHINode *val5 = Builder.CreatePHI(IntT, 2);

    //     %6 = sub nuw nsw i32 64, %5
    Value *val6 = Builder.CreateSub(toInt(64), val5, "", true, true);

    //     br label %13
    Builder.CreateBr(BB13);

    //     7:                                                ; preds = %10
    Builder.SetInsertPoint(BB7);

    //     tail call void (...) @simFlush() #2
    Builder.CreateCall(simFlushF);

    //     %8 = add nuw nsw i32 %2, 1
    Value *val8 = Builder.CreateAdd(val2, toInt(1), "", true, true);

    //     %9 = icmp eq i32 %8, 200
    Value *val9 = Builder.CreateICmpEQ(val8, toInt(200));

    //     br i1 %9, label %3, label %1
    Builder.CreateCondBr(val9, BB3, BB1);

    //     10:                                               ; preds = %32
    Builder.SetInsertPoint(BB10);

    //     %11 = add nuw nsw i32 %5, 1
    Value* val11 = Builder.CreateAdd(val5, toInt(1), "", true, true);

    //     %12 = icmp eq i32 %11, 64
    Value *val12 = Builder.CreateICmpEQ(val11, toInt(64));

    //     br i1 %12, label %7, label %4
    Builder.CreateCondBr(val12, BB7, BB4);

    //     13:                                               ; preds = %4, %32
    Builder.SetInsertPoint(BB13);

    //     %14 = phi i32 [ 0, %4 ], [ %33, %32 ]
    PHINode *val14 = Builder.CreatePHI(IntT, 2);

    //     %15 = tail call i32 @simGetPixel(i32  %14, i32  %5) #2
    Value *val15 = Builder.CreateCall(simGetPixelF, {val14, val5});

    //     %16 = tail call i32 @simGetLength(i32  %14, i32  %5) #2
    Value *val16 = Builder.CreateCall(simGetLengthF, {val14, val5});

    //     %17 = icmp eq i32 %15, -16711936
    Value *val17 = Builder.CreateICmpEQ(val15, toInt(-16711936));

    //     %18 = icmp sgt i32 %16, 0
    Value *val18 = Builder.CreateICmpSGT(val16, toInt(0));

    //     %19 = select i1 %17, i1 %18, i1 false
    Value *val19 = Builder.CreateSelect(val17, val18, toInt(0));

    //     br i1 %19, label %20, label %32
    Builder.CreateCondBr(val19, BB20, BB32);

    //     20:                  ; preds = %13
    Builder.SetInsertPoint(BB20);
                                 
    //     %21 = tail call i32 @simRand(i32  -1, i32  1) #2
    Value *val21 = Builder.CreateCall(simRandF, {toInt(-1), toInt(1)});

    //     %22 = tail call i32 @simRand(i32  1, i32  1) #2
    Value *val22 = Builder.CreateCall(simRandF, {toInt(1), toInt(1)});

    //     %23 = mul nsw i32 %21, %16
    Value *val23 = Builder.CreateMul(val21, val16, "", false, true);

    //     %24 = add nsw i32 %23, %14
    Value *val24 = Builder.CreateAdd(val23, val14, "", false, true);

    //     %25 = mul nsw i32 %22, %16
    Value *val25 = Builder.CreateMul(val22, val16, "", false, true);

    //     %26 = add nsw i32 %25, %5
    Value *val26 = Builder.CreateAdd(val25, val5, "", false, true);

    //     %27 = tail call i32 @simMixColors(i32  -16711936, i32  -16751104, i32  %5, i32  %6) #2
    Value *val27 = Builder.CreateCall(simMixColorsF, {toInt(-16711936), toInt(-16751104), val5, val6});

    //     tail call void @simPutPixel(i32  %24, i32  %26, i32  %27) #2
    Builder.CreateCall(simPutPixelF, {val24, val26, val27});

    //     %28 = tail call i32 @simRand(i32  -1, i32  1) #2
    Value *val28 = Builder.CreateCall(simRandF, {toInt(-1), toInt(1)});

    //     %29 = mul nsw i32 %28, %16
    Value *val29 = Builder.CreateMul(val28, val16, "", false, true);

    //     %30 = add nsw i32 %29, %14
    Value *val30 = Builder.CreateAdd(val29, val14, "", false, true);

    //     %31 = tail call i32 @simRand(i32  1, i32  %16) #2
    Value *val31 = Builder.CreateCall(simRandF, {toInt(1), val16});

    //     tail call void @simPutSpring(i32  %30, i32  %26, i32  -16711936, i32  %31) #2
    Builder.CreateCall(simPutSpringF, {val30, val26, toInt(-16711936), val31});

    //     br label %32
    Builder.CreateBr(BB32);

    //     32:                                               ; preds = %20, %13
    Builder.SetInsertPoint(BB32);

    //     %33 = add nuw nsw i32 %14, 1
    Value* val33 = Builder.CreateAdd(val14, toInt(1), "", true, true);

    //     %34 = icmp eq i32 %33, 128
    Value* val34 = Builder.CreateICmpEQ(val33, toInt(128)); 

    //     br i1 %34, label %10, label %13
    Builder.CreateCondBr(val34, BB10, BB13);

    // Add incomings
    val5->addIncoming(toInt(0), BB1);
    val5->addIncoming(val11, BB10);

    val2->addIncoming(toInt(0), BB0);
    val2->addIncoming(val8, BB7);

    val14->addIncoming(toInt(0), BB4);
    val14->addIncoming(val33, BB32);
    //________________________________DUMP_IR________________________________________

    // Dump LLVM IR
    std::error_code errCode;
    raw_fd_ostream OS(FILE_IR, errCode);
    module->print(OS, nullptr);

    llvm::errs() << "LLVM IR в файле " << FILE_IR << "\n";

    //_____________________________INTERPRETATION____________________________________

    // LLVM IR Interpreter
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();

    ExecutionEngine *execEngine = EngineBuilder(std::unique_ptr<Module>(module)).create();

    #define TR(func) if (FuncName == #func) {return reinterpret_cast<void *>(func);}

        execEngine->InstallLazyFunctionCreator([&](const std::string &FuncName) -> void * {
            TR(simPutSpring);
            TR(simFlush);
            TR(simGetPixel);
            TR(simGetLength);
            TR(simRand);
            TR(simPutPixel);
            TR(simMixColors);
            
            return nullptr;
        });

    #undef TR

    execEngine->finalizeObject();

    simInit();

    ArrayRef<GenericValue> NoArgs;
    execEngine->runFunction(appDef, NoArgs);

    simExit();
    return EXIT_SUCCESS;
}