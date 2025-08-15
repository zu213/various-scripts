// Chat gpt code
import fs from 'fs';
import path from 'path';

function transformContent(content) {
  let result = '';
  for (let i = 0; i < content.length; i++) {
    const current = content[i];
    const next = content[i + 1];

    // Check: current is lowercase, next is uppercase
    if (current >= 'a' && current <= 'z' && next && next >= 'A' && next <= 'Z') {
      result += current + '-' + next.toLowerCase();
      i++;
    } else {
      result += current;
    }
  }
  return result;
}

function processFile(filePath) {
  let content = fs.readFileSync(filePath, 'utf-8');
  let transformed = transformContent(content);

  if (transformed !== content) {
    fs.writeFileSync(filePath, transformed, 'utf-8');
    console.log(`Updated: ${filePath}`);
  } else {
    console.log(`No changes: ${filePath}`);
  }
}

function processPath(inputPath) {
  const stats = fs.statSync(inputPath);

  if (stats.isFile()) {
    processFile(inputPath);
  } else if (stats.isDirectory()) {
    const files = fs.readdirSync(inputPath);
    files.forEach(file => {
      const fullPath = path.join(inputPath, file);
      if (fs.statSync(fullPath).isFile()) {
        processFile(fullPath);
      }
    });
  } else {
    console.error('Invalid path provided.');
  }
}

const targetPath = process.argv[2];
if (!targetPath) {
  console.error('Usage: node transformChars.js <file-or-folder-path>');
  process.exit(1);
}

processPath(path.resolve(targetPath));
