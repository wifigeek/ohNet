import os
import sys
import subprocess
import time
import shutil
import signal

def objPath():
    plat = 'Posix'
    if os.name == 'nt':
        plat = 'Windows'
    variant = 'Debug'
    if gReleaseBuild == 1:
        variant = 'Release'
    path = os.path.join('Build', 'Obj', plat, variant)
    return path

def build(aTarget):
    buildCmd = 'make '
    if os.name == 'nt':
        buildCmd = 'nmake -s -f OhNet.mak '
    buildCmd += aTarget
    if os.environ.has_key('CS_PLATFORM'):
        buildCmd += ' csplatform=' + os.environ['CS_PLATFORM']
    if gReleaseBuild == 1:
        buildCmd += ' release=1'
    ret = os.system(buildCmd)
    if (0 != ret):
        print '\nBuild for ' + aTarget + ' failed, aborting'
        sys.exit(1)

def runBuilds():
    if gIncremental == 0:
        cleanCmd = ''
        if os.name == 'nt':
            cleanCmd = 'nmake /s /f OhNet.mak clean'
        else:
            cleanCmd = 'make clean'
        os.system(cleanCmd)
    build('all')
    print '\nBuilds complete'

def runTests():
    testsToRun = list(gAllTests)
    if gFullTests != 1:
        # Suppress non-quick tests
        testsToRun = [test for test in testsToRun if test.quick]
    if gNativeTestsOnly == 1:
        # Suppress non-native tests
        testsToRun = [test for test in testsToRun if test.native]
    for test in testsToRun:
        print '\nTest: ' + test.name
        cmdLine = test.args
        cmdLine.insert(0, test.Path())
        if (not test.native and os.name != 'nt'):
            cmdLine.insert(0, 'mono')
        ret = subprocess.call(cmdLine)
        if ret != 0:
            print '\nTest ' + test.name + ' failed, aborting'
            sys.exit(1)

def runTestsValgrind():
    # clear any old output files
    outputDir = 'vgout'
    if os.path.exists(outputDir):
        shutil.rmtree(outputDir)
    os.mkdir(outputDir)
    failed = []
    testsToRun = [test for test in gAllTests if test.quick and test.native]
    if gFullTests == 1:
        testsToRun = [test for test in gAllTests if test.native]
    os.system('export GLIBCXX_FORCE_NEW')
    for test in testsToRun:
        print '\nTest: ' + test.name
        cmdLine = []
        cmdLine.append('valgrind')
        cmdLine.append('--leak-check=yes')
        cmdLine.append('--suppressions=ValgrindSuppressions.txt')
        cmdLine.append('--xml=yes')
        cmdLine.append('--xml-file=' + os.path.join(outputDir, test.name) + '.xml')
        cmdLine.append(test.Path())
        for arg in test.args:
            cmdLine.append(arg)
        ret = subprocess.call(cmdLine)
        if ret != 0:
            failed.append(test.name)
    if len(failed) > 0:
        print '\nERROR, the following tests failed:'
        for fail in failed:
            print '\t' + fail
        sys.exit(-1)

def runTestsHelgrind():
    # clear any old output files
    outputDir = 'hgout'
    if os.path.exists(outputDir):
        shutil.rmtree(outputDir)
    os.mkdir(outputDir)
    failed = []
    testsToRun = [test for test in gAllTests if test.quick and test.native]
    if gFullTests == 1:
        testsToRun = [test for test in gAllTests if test.native]
    os.system('export GLIBCXX_FORCE_NEW')
    for test in testsToRun:
        print '\nTest: ' + test.name
        cmdLine = []
        cmdLine.append('valgrind')
        cmdLine.append('--tool=helgrind')
        cmdLine.append('--xml=yes')
        cmdLine.append('--xml-file=' + os.path.join(outputDir, test.name) + '.xml')
        cmdLine.append(test.Path())
        for arg in test.args:
            cmdLine.append(arg)
        ret = subprocess.call(cmdLine)
        if ret != 0:
            failed.append(test.name)
    if len(failed) > 0:
        print '\nERROR, the following tests failed:'
        for fail in failed:
            print '\t' + fail
        sys.exit(-1)

gStartTime = time.strftime('%H:%M:%S')
gBuildsCompleteTime = ''
gBuildOnly = 0
gFullTests = 0
gIncremental = 0
gNativeTestsOnly = 0
gSilent = 0
gTestsOnly = 0
gValgrind = 0
gHelgrind = 0
gJsTests = 0
gReleaseBuild = 0
for arg in sys.argv[1:]:
    if arg == '-b' or arg == '--buildonly':
        gBuildOnly = 1
    elif arg == '-f' or arg == '--full':
        gFullTests = 1
    elif arg == '-i' or arg == '--incremental':
        gIncremental = 1
    elif arg == '-n' or arg == '--native':
        gNativeTestsOnly = 1
    elif arg == '-s' or arg == '--silent':
        gSilent = 1
    elif arg == '-j' or arg == '--js':
        gJsTests = 1
    elif arg == '-t' or arg == '--testsonly':
        gTestsOnly = 1
    elif arg == '-vg' or arg == '--valgrind':
        gValgrind = 1
        if os.name == 'nt':
            print 'ERROR - valgrind is only supported on linux'
            sys.exit(1)
    elif arg == '-hg' or arg == '--helgrind':
        gHelgrind = 1
        if os.name == 'nt':
            print 'ERROR - helgrind is only supported on linux'
            sys.exit(1)
    elif arg == '-r' or arg == '--release':
        gReleaseBuild = 1
    else:
        print 'Unrecognised argument - ' + arg
        sys.exit(1)
    os.environ["ABORT_ON_FAILURE"] = "1"
    if gSilent != 0:
        os.environ["NO_ERROR_DIALOGS"] = "1"

class TestCase(object):
    def __init__(self, name, args, quick=False, native=True):
        self.name = name
        self.args = args
        self.quick = quick
        self.native = native
    def Path(self):
        path = objPath() + '/' + self.name
        if os.name == 'nt':
            path += '.exe'
        elif not self.native:
            os.environ['LD_LIBRARY_PATH'] = objPath()
            path += '.exe'
        else:
            path += '.elf'
        return path

gAllTests = [ TestCase('TestBuffer', [], True)
             ,TestCase('TestThread', [], True)
             ,TestCase('TestFifo', [], True)
             ,TestCase('TestQueue', [], True)
             ,TestCase('TestNetwork', [], True)
             ,TestCase('TestTimer', [])
             ,TestCase('TestSsdpMListen', ['-d', '10'], True)
             ,TestCase('TestSsdpUListen', ['-t', 'av.openhome.org:service:Radio:1'], True)
             ,TestCase('TestDeviceList', ['-t', 'av.openhome.org:service:Radio:1', '-f'], True)
             ,TestCase('TestDeviceListStd', ['-t', 'av.openhome.org:service:Radio:1', '-f'], True)
             ,TestCase('TestDeviceListC', ['-t', 'av.openhome.org:service:Radio:1', '-f'], True)
             ,TestCase('TestInvocation', [])
             ,TestCase('TestInvocationStd', [])
             ,TestCase('TestSubscription', [])
             ,TestCase('TestProxyC', [])
             ,TestCase('TestDviDiscovery', ['-l'], True)
             ,TestCase('TestDviDeviceList', ['-l'], True)
             ,TestCase('TestDvInvocation', ['-l'], True)
             ,TestCase('TestDvSubscription', ['-l'], True)
             ,TestCase('TestDvDeviceStd', ['-l'], True)
             ,TestCase('TestDvDeviceC', [], True)
             ,TestCase('TestCpDeviceDv', [], True)
             ,TestCase('TestCpDeviceDvStd', [], True)
             ,TestCase('TestCpDeviceDvC', [], True)
             ,TestCase('TestProxyCs', [], False, False)
             ,TestCase('TestDvDeviceCs', [], True, False)
             ,TestCase('TestCpDeviceDvCs', [], True, False)
            ]

def JsTests():
    print "running javascript tests"
    if not os.path.exists("xout"):
        os.mkdir("xout")
    jsfailed = open("xout/ProxyJsTest.xml", "w")
    jsfailed.writelines('<?xml version="1.0" encoding="UTF-8"?><testsuites><testsuite name="Test Proxy" tests="1" failures="1" time="0.01"><testcase name="No Results Output" time="0.01"><failure message="No XML Results Output from JS Proxy Tests."><![CDATA[No XML Results Output from JS Proxy Tests.]]></failure></testcase></testsuite></testsuites>')
    jsfailed.close()
    localAppData = os.environ.get('ProgramFiles')
    uiPath = os.path.join(os.getcwd(), 'Build\Include\Js\Tests')
    browser = os.path.join(localAppData, 'Safari\Safari.exe')
    testbasic = subprocess.Popen([os.path.join(objPath(), 'TestDvTestBasic.exe'), '-l', '-c', uiPath])
    devfinder = subprocess.Popen([os.path.join(objPath(), 'TestDeviceFinder.exe'), '-l', '-s', 'openhome.org:service:TestBasic:1'],stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    devfinder_out = devfinder.communicate()[1].rstrip()
    subprocess.call([browser, devfinder_out])
    testbasic.terminate()

if gTestsOnly == 0:
    runBuilds()
gBuildsCompleteTime = time.strftime('%H:%M:%S')
if gBuildOnly == 0:
    if gValgrind == 1:
        runTestsValgrind()
    if gHelgrind == 1:
        runTestsHelgrind()
    if gValgrind == 0 and gHelgrind == 0:
        runTests()
    if gJsTests == 1:
        JsTests()
    print '\nFinished.  All tests passed'
print 'Start time: ' + gStartTime
print 'Builds complete: ' + gBuildsCompleteTime
print 'End time: ' + time.strftime('%H:%M:%S')
