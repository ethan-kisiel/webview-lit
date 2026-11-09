import {defineConfig} from 'vitest/config';
import {viteSingleFile} from 'vite-plugin-singlefile';

export default defineConfig({
  plugins: [viteSingleFile()],
  test: {
    environment: 'jsdom',
  },
  build: {
    // Optional: disable asset chunking warnings or customize output if needed
  },
});
